#include "unison-oscillator.h"

namespace synth80s
{
  UnisonOscillator::UnisonOscillator(AudioContext* audioContext)
  : AudioProcessor(audioContext)
  {
    const int BLOCK_SIZE = this->audioContext->getFramesPerBuffer();
    this->outputBlock = new float[BLOCK_SIZE]();
    
    // create the oscillators, buffers and notes for the unison oscillators
    for (int i = 0; i < UnisonOscillator::OSC_COUNT; i++)
    {
		this->oscillatorArray.push_back(new MultishapeOscillator(this->audioContext));
		
		this->bufferArray.push_back(nullptr);
		
		this->frequencyArray.push_back(this->note.getFrequency());
	}
  }

  float* UnisonOscillator::getProcessedOutput() { return this->outputBlock; }

  void UnisonOscillator::process(float* inputBlock)
  {
    const int BLOCK_SIZE = this->audioContext->getFramesPerBuffer();

    // make all the oscillator generate their output
    float currentFrequency = 0.0;
    const int DETUNE_START_INDEX = static_cast<int> (UnisonOscillator::OSC_COUNT / (-2)); 
    for (int oscIndex = 0; oscIndex < UnisonOscillator::OSC_COUNT; oscIndex++)
    {
	    // compute the frequency of the current oscillator
      this->note.setCentsOffset( (DETUNE_START_INDEX + oscIndex) * this->unisonCentsDetune);
      this->frequencyArray[oscIndex] = this->note.getFrequency();
		
	    // set the frequency for the current oscillator and then process the sound of that oscillator
      this->oscillatorArray[oscIndex]->setFrequency(this->frequencyArray[oscIndex]);
      this->oscillatorArray[oscIndex]->process();

      // save the output array pointer of the current oscillator
      this->bufferArray[oscIndex] = this->oscillatorArray[oscIndex]->getProcessedOutput();
    }
    
    // combine the oscillators output and store it into the output block of this class
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
      // always reset current element before recomputing
      this->outputBlock[i] = 0.0f;
        
      for (int oscIndex = 0; oscIndex < UnisonOscillator::OSC_COUNT; oscIndex++)
      {
        this->outputBlock[i] += this->bufferArray[oscIndex][i];
      }
    }
  }

  void UnisonOscillator::setUnisonDetune(int centsDetune)
  {
    this->unisonCentsDetune = centsDetune;
  }

  void UnisonOscillator::setMainNote(Note note)
  {
	this->note.setMainParams(note);
  }
  
  void UnisonOscillator::setOctavesAndSemitones(int octaves, int semitones)
  {
      this->note.setOctavesAndSemitones(octaves, semitones);
  }
  
  void UnisonOscillator::setOctavesOffset(int octaves)
  {
	this->note.setOctavesOffset(octaves);
  }
  
  void UnisonOscillator::setSemitonesOffset(int semitones)
  {
	this->note.setSemitonesOffset(semitones);
  }
  
  void UnisonOscillator::setTriangleWeight(float weight)
  {
	for (int oscIndex = 0; oscIndex < UnisonOscillator::OSC_COUNT; oscIndex++)
    {
		this->oscillatorArray[oscIndex]->setTriangleWeight(weight);
	}
  }
  
  void UnisonOscillator::setSawtoothWeight(float weight)
  {
	for (int oscIndex = 0; oscIndex < UnisonOscillator::OSC_COUNT; oscIndex++)
    {
		this->oscillatorArray[oscIndex]->setSawtoothWeight(weight);
	}
  }
  
  void UnisonOscillator::setSquareWeight(float weight)
  {
	for (int oscIndex = 0; oscIndex < UnisonOscillator::OSC_COUNT; oscIndex++)
    {
		this->oscillatorArray[oscIndex]->setSquareWeight(weight);
	}
  }

  // sets the gain
  void UnisonOscillator::setGain(float gain)
  {
    this->gain = gain;
  }
}
