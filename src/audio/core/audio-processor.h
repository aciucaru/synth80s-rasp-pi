#ifndef SYNTH80S_SRC_AUDIO_CORE_AUDIO_PROCESSOR_H

#define SYNTH80S_SRC_AUDIO_CORE_AUDIO_PROCESSOR_H

#include "audio-context.h"

namespace synth80s
{
    class AudioProcessor
    {
        protected:
            // the audio context, usefull for retrieving the 'sampling rate' and other information
            AudioContext* audioContext;

        public:
            AudioProcessor(AudioContext* audioContext);

            /* virtual (abstract) method, is responsible for generating the actual signal of the AudioProcessor;
            ** this method processes one audio block at a time.
            ** this method should be implemented by any subclass, with a specific implementation. */ 
            virtual void process(float* inputBlock = nullptr) = 0;

            /* method that returns the latest processed output.
            ** this should also be implemtned by any subclass.
            ** this method can return the last processed output block many times. */
            virtual float* getProcessedOutput() = 0;
    };
}

#endif