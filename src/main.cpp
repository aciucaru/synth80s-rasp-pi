/* PortAudio installtion instructions:
 * 1. download portasudio library and unzip
 * 2. change directory
 * 3. build:
 * ./configure && make
 * 4. install globally:
 * sudo make install
 * 5. update the system to see new library (because it wasn't installed with apt/ apt-get:
 * sudo ldconfig
 *
 * to compile run the bash script:
 * ./build-desktop.sh
 */

// Always include RtAudio library first, otherwise we get weird compilation error
#include "../libs/RtAudio.h" // must be included first!

#include "audio/core/audio-context.h"
#include "rpi/sequencer-synth.h"

#include <iostream>
#include <unistd.h> // for usleep()
#include <signal.h> // for signal()

// The audio context, it holds the settings for audio generation (sample rate, block size)
synth80s::AudioContext* audioContext = new synth80s::AudioContext(44100, 512); // min. 512

// The synthesizer, this is the source of sound
synth80s::SequencerSynth soundSource(audioContext);

unsigned int device = 0;
unsigned int channels = 1;
unsigned int bufferFrames = audioContext->getFramesPerBuffer();
unsigned int offset = 0;
double* data = (double*) calloc(channels, sizeof( double ));

bool done;
void finish(int someValue)
{
    done = true;
}

void errorCallback(RtAudioErrorType /*type*/, const std::string &errorText)
{
  // This example error handling function simply outputs the error message to stderr.
  std::cerr << "errorCallback: " << errorText << std::endl;
}

// instantiate the DAC and specify our own error callback function.
RtAudio dac( RtAudio::UNSPECIFIED, &errorCallback );

int instanceCallback(void* outputBuffer, void* /*inputBuffer*/, unsigned int nBufferFrames,
                                    double streamTime, RtAudioStreamStatus status, void* data)
{
    float* buffer = (float*) outputBuffer;

    // Generate the audio
    soundSource.process();

    // Get the generated audio (as float array)
    const float* synthOutput = soundSource.getProcessedOutput();

    // Copy the processed sound
    for (unsigned int i = 0; i < nBufferFrames; i++)
    {
        buffer[i] = synthOutput[i];
    }

    return 0;
}

// Sleep routine
void sleep(int milliseconds)
{
    usleep( (unsigned long) (milliseconds * 1000.0) );
}

void cleanup(RtAudio& dac, double* data)
{
    if (dac.isStreamOpen())
        dac.closeStream();

    free(data);
}

int main(int argc, char *argv[])
{
    // **************** Audio code **************************************************
    std::vector<unsigned int> deviceIds = dac.getDeviceIds();
    if (deviceIds.size() < 1)
    {
        std::cout << "No audio devices found!" << std::endl;
        exit(1);
    }

    // Tell RtAudio to output all messages, even warnings.
    dac.showWarnings(true);

    // Set our stream parameters, this object will be used only for output settings
    RtAudio::StreamParameters oParams;
    // Set our stream parameters for output only.
    oParams.nChannels = channels;
    oParams.firstChannel = offset;

    if (device == 0)
        oParams.deviceId = dac.getDefaultOutputDevice();
    else
        std::cout << "ERROR: could not get device 0" << std::endl;

    // RtAudio strea, option
    RtAudio::StreamOptions options;
    options.flags = RTAUDIO_HOG_DEVICE;
    options.flags |= RTAUDIO_SCHEDULE_REALTIME;

    if (dac.openStream(&oParams,
                        NULL,
                        RTAUDIO_FLOAT32,
                        audioContext->getSampleRate(),
                        &bufferFrames,
                        &instanceCallback,
                        (void*)data,
                        &options))
    {
        std::cout << dac.getErrorText() << std::endl;
        cleanup(dac, data);

        return 0;
    }

    if (dac.isStreamOpen() == false)
    {
        cleanup(dac, data);
        return 0;
    }

    // Stream is open ... now start it.
    if (dac.startStream())
    {
        std::cout << dac.getErrorText() << std::endl;
        cleanup(dac, data);
        return 0;
    }

    std::cout << "\nPlaying ... quit with Ctrl-C (buffer size = " << bufferFrames << ").\n";

    // Install an interrupt handler function.
    done = false;
    (void) signal(SIGINT, finish);

    while (!done && dac.isStreamRunning())
    {
        sleep(100);
    }

    // Block released ... stop the stream
    if (dac.isStreamRunning())
        dac.stopStream(); // or could call dac.abortStream();

    cleanup(dac, data);

    return 0;
}
