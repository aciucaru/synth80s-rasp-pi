#ifndef SYNTH80S_SRC_AUDIO_SEQUENCER_NOTE_SEQUENCE_H

#define SYNTH80S_SRC_AUDIO_SEQUENCER_NOTE_SEQUENCE_H

#include <array>

namespace synth80s
{
    struct NoteSequence
    {
		// The data members of this structure:
		// - the number of steps this sequence has to offer (not all 8 steps are
		//   necessarily used)
		// - an array of semitones offsets
		int numberOfSteps = 4;
		std::array<int, 8> noteSequence = {0, 1, 2, 3, 4, 5, 6, 7};
	};
}

#endif
