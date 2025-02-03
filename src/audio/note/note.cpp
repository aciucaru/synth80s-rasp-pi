#include "note.h"

namespace synth80s
{
    Note::Note() { }

    Note::Note(int octaves, int semitones)
    : octaves(octaves),
        semitones(semitones)
    {

    }

    void Note::setOctavesAndSemitones(int octaves, int semitones)
    {
        this->octaves = octaves;
        this->semitones = semitones;

        // now also recompute the frequency corresponding to this note
        this->recomputeFreq();
    }
    
    void Note::setMainParams(Note note)
    {
		this->octaves = note.octaves;
        this->semitones = note.semitones;
        this->octavesOffset = note.octavesOffset;
        this->semitonesOffset = note.semitonesOffset;

        // now also recompute the frequency corresponding to this note
        this->recomputeFreq();
	}
	
	void Note::setOctaves(int octaves)
	{
		this->octaves = octaves;
	}
    
    int Note::getOctaves() { return this->octaves; }
    
    void Note::setSemitones(int semitones)
    {
		this->semitones = semitones;
	}
	
    int Note::getSemitones() { return this->semitones; }

    void Note::setOctavesOffset(int octavesOffset)
    {
        this->octavesOffset = octavesOffset;

        // now also recompute the frequency corresponding to this note
        this->recomputeFreq();
    }

    void Note::setSemitonesOffset(int semitonesOffset)
    {
        this->semitonesOffset = semitonesOffset;

        // now also recompute the frequency corresponding to this note
        this->recomputeFreq();
    }

    void Note::setCentsOffset(int centsOffset)
    {
        this->centsOffset = centsOffset;

        // now also recompute the frequency corresponding to this note
        this->recomputeFreq();
    }

    float Note::getFrequency() { return this->freq; }

    void Note::recomputeFreq()
    {
        // the octave corresponding to A4 note
        const int A4_OCTAVES = 4;

        // the number of semitones (added to the previous 'octave) corresponding to A4 note
        const int A4_SEMITONES = 9;

        // the frequency corresponding to A4 note; usualy it's 440 Hz, but may also have other values (443 Hz)
        const float A4_FREQ = 440.0f;

        // compute the number of offset semitones relative to A4 note
        const float semitonesOffset = (float)((this->octaves + this->octavesOffset - A4_OCTAVES) * 12.0f +
                                        this->semitones + this->semitonesOffset - A4_SEMITONES +
                                        this->centsOffset / 100.0f);

        // recompute frequency based on semitones offset from A4 note
        this->freq = A4_FREQ * pow(2.0f, semitonesOffset / 12.0f);
    }
}
