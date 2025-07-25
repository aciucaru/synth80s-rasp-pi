#ifndef SYNTH80S_SRC_AUDIO_NOTE_NOTE_H

#define SYNTH80S_SRC_AUDIO_NOTE_NOTE_H

#include <cmath>

namespace synth80s
{
    class Note
    {
        private:
            // main parameters of a note: octaves and semitones
            int octaves = 4; // 4th octave, the middle octave
            int semitones = 9; // A note

            // offset parameters for oscillators:
            int octavesOffset = 0;
            int semitonesOffset = 0;
            int centsOffset = 0;

            // the final frequency of the note
            float freq = 440.0f; // default value corresponds to 4 'octaves' and 9 'semitones'

        public:
            Note();
            Note(int octaves, int semitones);

            void setOctavesAndSemitones(int octaves, int semitones);
            void setMainParams(Note note);
            
            void setOctaves(int octaves);
            int getOctaves();
            
            void setSemitones(int semitones);
            int getSemitones();

            void setOctavesOffset(int octavesOffset);

            void setSemitonesOffset(int semitonesOffset);

            void setCentsOffset(int centsOffset);

            float getFrequency();

        private:
            void recomputeFreq();
    };
}

#endif
