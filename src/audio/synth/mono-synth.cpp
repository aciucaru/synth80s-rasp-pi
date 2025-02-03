#include "mono-synth.h"

namespace synth80s
{
  MonoSynth::MonoSynth(AudioContext* audioContext)
                    : AudioProcessor(audioContext),
                      oscillator1(audioContext)
  {
    const int BLOCK_SIZE = this->audioContext->getFramesPerBuffer();
    this->outputBlock = new float[BLOCK_SIZE]();
  }

  float* MonoSynth::getProcessedOutput() { return this->outputBlock; }

  void MonoSynth::process(float* inputBlock)
  {
    const int BLOCK_SIZE = this->audioContext->getFramesPerBuffer();

    // make the oscillators generate their output
    this->oscillator1.process();

    // get the output blocks of the oscillator
    float* osc1Block = this->oscillator1.getProcessedOutput();

    // combine the oscillators output and store it into the output block of this class
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
      this->outputBlock[i] = this->gain * osc1Block[i];                              
    }
  }

  UnisonOscillator& MonoSynth::getOscillator() { return this->oscillator1; }
}
