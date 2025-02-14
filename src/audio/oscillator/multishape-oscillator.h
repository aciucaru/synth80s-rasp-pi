#ifndef SYNTH80S_SRC_AUDIO_OSCILLATOR_MULTISHAPE_OSCILLATOR_H

#define SYNTH80S_SRC_AUDIO_OSCILLATOR_MULTISHAPE_OSCILLATOR_H

#include "../core/audio-context.h"
#include "../core/audio-processor.h"
#include "melodic-oscillator.h"
#include "triangle-oscillator.h"
#include "sawtooth-oscillator.h"
#include "square-oscillator.h"

#include <cmath>

namespace synth80s
{
  class MultishapeOscillator: public AudioProcessor
  {
    private:
      // the oscillators
      TriangleOscillator triangleOscillator;
      SawtoothOscillator sawtoothOscillator;
      SquareOscillator squareOscillator;

      // the buffers (arrays) corresponding to each oscillator
      float* triangleOscBlock = nullptr;
      float* sawtoothOscBlock = nullptr;
      float* squareOscBlock = nullptr;

      // the weights of the oscillators
      float triangleOscWeight = 1.0f;
      float sawtoothOscWeight = 0.0f;
      float squareOscWeight = 0.0f;

      // the gain of the oscillator, this is a multiplier used to increase or lower the
      // volume of the socillator
      float gain = 1.0f;

      // the actual block (array) of audio samples generated by this class
      float* outputBlock = nullptr;

    public:
      // constructor, must receive AudioContext as external dependecy
      MultishapeOscillator(AudioContext* audioContext);

      /* implementation of virtual (abstract) method, inherited from 'AudioProcessor' class;
      ** the signal is stored into the 'block' buffer inherited from 'AudioNode' class;
      ** this method is responsible for generating the actual wave; */
      void process(float* inputBlock = nullptr) override;

      // implementation of abstract method, inherited from 'AudioProcessor' class
      float* getProcessedOutput() override;

	  // these methods set the weights of each oscillator
      void setTriangleWeight(float weight);
      void setSawtoothWeight(float weight);
      void setSquareWeight(float weight);

      void setFrequency(float frequency);
      void setGain(float gain);
  };
}

#endif

