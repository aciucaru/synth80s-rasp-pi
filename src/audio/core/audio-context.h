#ifndef SYNTH80S_SRC_AUDIO_CORE_AUDIO_CONTEXT_H

#define SYNTH80S_SRC_AUDIO_CORE_AUDIO_CONTEXT_H

namespace synth80s
{
  class AudioContext
  {
    private:
      // the sample rate
      int sampleRate = 44100;

      // the number of samples per buffer (channel), 32 is Arduino example default
      int framesPerBuffer = 32;

    public:
      AudioContext(int sampleRate, int framesPerBuffer);

      int getSampleRate();
      int getFramesPerBuffer();
  };
}

#endif
