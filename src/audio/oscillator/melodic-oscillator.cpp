#include "melodic-oscillator.h"

namespace synth80s
{
  MelodicOscillator::MelodicOscillator(AudioContext* audioContext)
  : AudioProcessor(audioContext)
  {
    const int BLOCK_SIZE = this->audioContext->getFramesPerBuffer();

    this->outputBlock = new float[BLOCK_SIZE]();
  }

  float* MelodicOscillator::getProcessedOutput() { return this->outputBlock; }

  void MelodicOscillator::incrementPhase()
  {
    const int sampleRate = this->audioContext->getSampleRate();
    float deltaPhase = this->frequency / sampleRate;

    /* Increment the phase.
    ** The incrementation should be based on frequency (not 'deltaPhase'), so we
    ** can have time-varying frequency */
    deltaPhase = this->frequency / sampleRate; // first, determine the increment
    this->phase += deltaPhase; // then, increment phase

    /* Check if the 'phase' has grown to much, in order to prevent 32 bit float number overflow;
    ** We dont't need to reach the limit of a 'float' number, 2PI is a suficcient limit;
    ** If the phase is greather than 2PI, then we reset it to zero; */
    if (this->phase > 2.0f * M_PI)
      this->phase -= 2.0f * M_PI; // we reset by subtracting, never by assignment!
  }

  // sets the frequency
  void MelodicOscillator::setFrequency(float frequency)
  {
    this->frequency = frequency;
  }

  // sets the gain
  void MelodicOscillator::setGain(float gain)
  {
    this->gain = gain;
  }
}
