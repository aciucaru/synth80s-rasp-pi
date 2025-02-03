# Build script for Linux desktop version, with RtAudio library.
g++ -D__LINUX_ALSA__ -o synth80s \
    src/utils/math-util.cpp \
    src/audio/core/audio-context.cpp \
    src/audio/core/audio-processor.cpp \
    src/audio/oscillator/melodic-oscillator.cpp \
    src/audio/oscillator/sawtooth-oscillator.cpp \
    src/audio/oscillator/sine-oscillator.cpp \
    src/audio/oscillator/square-oscillator.cpp \
    src/audio/oscillator/triangle-oscillator.cpp \
    src/audio/oscillator/multishape-oscillator.cpp \
    src/audio/oscillator/unison-oscillator.cpp \
    src/audio/filter/moog-low-pass-filter.cpp \
    src/audio/sequencer/step-signal.cpp \
    src/audio/sequencer/asr-step-signal.cpp \
    src/audio/synth/mono-synth.cpp \
    src/audio/note/note.cpp \
    src/rpi/sequencer-synth.cpp \
    libs/RtAudio.cpp \
    src/main.cpp \
    -lasound -lpthread
