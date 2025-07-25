#include "sequencer-synth.h"

namespace synth80s
{
  SequencerSynth::SequencerSynth(AudioContext* audioContext)
                    : AudioProcessor(audioContext),
                      stepSignal(audioContext),
                      asrStepSignal(audioContext),
                      monoSynth(audioContext)
  {
    const int BLOCK_SIZE = this->audioContext->getFramesPerBuffer();

    this->outputBlock = new float[BLOCK_SIZE]();
    
    this->sequenceSemitoneOffsetArray = this->noteSequenceFactory.getSequence(0);
  }

  float* SequencerSynth::getProcessedOutput() { return this->outputBlock; }

  void SequencerSynth::process(float* inputBlock)
  {
	/* Make the hardware manager set it's internal parameter mode.
	 * If it's in 'READ_SYNTH_PARAMS' mode, then the values from the potentiometers
	 * are used for reading synth parameters values.
	 * If the mode is 'READ_STEP_FREQ', then the values from the potentiometers
	 * are used to read the frequencies (note semitones) of the notes of the step
	 * sequencer. */
	this->paramReader.readParamMode();
	
	/*  */
	this->paramReader.readIfDisplayEnabled();
	
    // First, read all the parameters for the synth. These are depenedent on the mode
    // set previously.
    // We read these parameters once per block (once per process() method call)
    const int OCTAVES_OFFSET = this->paramReader.readOctavesOffset();
    const int SEMITONES_OFFSET = this->paramReader.readSemitonesOffset();
    
    const float TRIANGLE_WEIGHT = this->paramReader.readTriangleWeight();
    const float SAWTOOTH_WEIGHT = this->paramReader.readSawtoothWeight();
    const float SQUARE_WEIGHT = this->paramReader.readSquareWeight();
    
    const int UNISON_DETUNE = this->paramReader.readUnisonDetune();
    
    const int SEQUENCER_BPM = this->paramReader.readSequencerBPM();
    
	this->gain = this->paramReader.readGain();
	
	// Read the note sequence (arpeggio) to be played
    const int NOTE_SEQUENCE_INDEX = this->paramReader.readSequenceIndex();
    
    // Get the number of steps corresponding to the selected note sequence
    // const int CURRENT_STEP_COUNT = this->stepSignal.getStepCount();
    const int CURRENT_STEP_COUNT = this->stepSignal.getStepCount();
    
    // Get the array of semitones corresponding to the selected note sequence
    this->sequenceSemitoneOffsetArray = this->noteSequenceFactory.getSequence(NOTE_SEQUENCE_INDEX);
    
    // Then, read the semitones offsets of the notes in the sequence
    for (int i = 0; i < CURRENT_STEP_COUNT; i++)
    {
      this->userSemitoneOffsetArray[i] = this->paramReader.readStepSemitonesOffset(i);
    }
    
    this->paramReader.updateDisplay();

    // First set the tempo of the step
    this->stepSignal.setBPM(SEQUENCER_BPM);
    
    // Then, make the step signal generate it's output and also store a pointer to it
    this->stepSignal.process();
    float* stepSignalOutput = this->stepSignal.getProcessedOutput();

    // Make the step signal generate it's output and also store a pointer to it
    this->asrStepSignal.process();
    float* asrStepSignalOutput = this->asrStepSignal.getProcessedOutput();

    /* Get the note corresponding to the step signal. We aproximate the
    ** note as corresponing to the first element of the block output.
    ** Because the step signal generates steps starting from 1, we subtract 1 to get correct index. */
    const int NOTE_INDEX = stepSignalOutput[0] - 1;

    // set the octaves, semitones and cents offsets
    this->noteArray[NOTE_INDEX].setOctavesOffset(OCTAVES_OFFSET);
    this->noteArray[NOTE_INDEX].setSemitonesOffset(SEMITONES_OFFSET + this->sequenceSemitoneOffsetArray[NOTE_INDEX] + userSemitoneOffsetArray[NOTE_INDEX]);

    this->monoSynth.getOscillator().setMainNote(this->noteArray[NOTE_INDEX]);
    this->monoSynth.getOscillator().setUnisonDetune(UNISON_DETUNE);
        
    this->monoSynth.getOscillator().setTriangleWeight(TRIANGLE_WEIGHT);
    this->monoSynth.getOscillator().setSawtoothWeight(SAWTOOTH_WEIGHT);
    this->monoSynth.getOscillator().setSquareWeight(SQUARE_WEIGHT);

    // Make the synth generate it's output and also store a pointer to it
    this->monoSynth.process();
    float* monoSynthOutput = this->monoSynth.getProcessedOutput();

    // combine the oscillators output and store it into the output block of this class
    const int BLOCK_SIZE = this->audioContext->getFramesPerBuffer();
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
      this->outputBlock[i] = this->gain * monoSynthOutput[i];
    }
  }
}
