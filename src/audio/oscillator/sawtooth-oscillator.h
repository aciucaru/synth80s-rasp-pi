#ifndef SYNTH80S_SRC_AUDIO_OSCILLATOR_SAWTOOTH_OSCILLATOR_H

#define SYNTH80S_SRC_AUDIO_OSCILLATOR_SAWTOOTH_OSCILLATOR_H

#include "../core/audio-context.h"
#include "melodic-oscillator.h"

#include <cmath>

namespace synth80s
{
  class SawtoothOscillator: public MelodicOscillator
  {
    public:
      // constructor, must receive AudioContext as external dependecy
      SawtoothOscillator(AudioContext* audioContext);

      /* implementation of virtual (abstract) method, inherited from 'AudioProcessor' class;
      ** the signal is stored into the 'block' buffer inherited from 'AudioNode' class;
      ** this method is responsible for generating the actual wave; */ 
      void process(float* inputBlock = nullptr) override;
  };
}

#endif

