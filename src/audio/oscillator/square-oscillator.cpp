#include "square-oscillator.h"

namespace synth80s
{
  SquareOscillator::SquareOscillator(AudioContext* audioContext)
  : MelodicOscillator(audioContext)
  { }

  void SquareOscillator::process(float* inputBlock)
  {
    // generate the values of the block buffer and fill that buffer
    // the buffer is internal to this class, inherited from 'AudioNode' class */
    const int BLOCK_SIZE = this->audioContext->getFramesPerBuffer();
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
      /* compute the actual sine value, the sin() uses 'phase' as main argument,
      ** which initial starts from 0.0f */
      this->outputBlock[i] = this->gain * synth80s::MathUtil::signum(std::sin(2.0f * M_PI * this->phase));

      // increment the phase required for computing next iteration value
      this->incrementPhase();
    }
  }
}
