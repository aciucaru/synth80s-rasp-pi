#include "audio-context.h"

namespace synth80s
{
  AudioContext::AudioContext(int sampleRate, int framesPerBuffer)
  {
    this->sampleRate = sampleRate;
    this->framesPerBuffer = framesPerBuffer;
  }

  int AudioContext::getSampleRate() { return this->sampleRate; }
  int AudioContext::getFramesPerBuffer() { return this->framesPerBuffer; }
}
