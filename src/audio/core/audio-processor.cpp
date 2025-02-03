#include "audio-processor.h"

namespace synth80s
{
    AudioProcessor::AudioProcessor(AudioContext* audioContext)
    {
        this->audioContext = audioContext;
    }
}