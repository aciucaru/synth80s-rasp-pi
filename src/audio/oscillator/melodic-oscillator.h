#ifndef SYNTH80S_SRC_AUDIO_OSCILLATOR_MELODIC_OSCILLATOR_H

#define SYNTH80S_SRC_AUDIO_OSCILLATOR_MELODIC_OSCILLATOR_H

#include "../core/audio-context.h"
#include "../core/audio-processor.h"

#include <cmath>

namespace synth80s
{
  class MelodicOscillator: public AudioProcessor
  {
    protected:
      // the argument to the sin() function (the angle fro mwich the sine is calculated)
      float phase = 0.0f;

      // the frequency of the oscillator, in Hertz
      float frequency = 440.0f;

      // the gain of the oscillator, this is a multiplier used to increase or lower the
      // volume of the socillator
      float gain = 1.0f;

      // the actual block (array) of audio samples generated by this class
      float* outputBlock = nullptr;

    protected:
      void incrementPhase();

    public:
      // constructor, must receive AudioContext as external dependecy
      MelodicOscillator(AudioContext* audioContext);

      // (abstract) method, inherited from 'AudioProcessor' class
      virtual void process(float* inputBlock = nullptr) = 0;

      // implementation of abstract method, inherited from 'AudioProcessor' class
      float* getProcessedOutput() override;

      // sets the frequency
      void setFrequency(float frequency);

      // sets the gain
      void setGain(float gain);
  };
}

#endif

