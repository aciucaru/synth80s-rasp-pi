#ifndef SYNTH80S_SRC_AUDIO_SEQUENCER_SEQUENCE_FACTORY_H

#define SYNTH80S_SRC_AUDIO_SEQUENCER_SEQUENCE_FACTORY_H

// #include "../note/note.h"
#include "note-sequence.h"

#include <iostream>
#include <array>

namespace synth80s
{
    class NoteSequenceFactory
    {
		private:
			static const int MAX_STEP_COUNT = 8;
			
			// This factory can provide 8 different sequences, these are the default sequences
			std::array<NoteSequence, 8> defaultNoteSequences =
			{{
				// Default sequence, no specific arpeggio/mellody
				{8, {0, 0, 0, 0, 0, 0, 0, 0}},
				
				// Minor Triad arpeggio,  root note: C, up-down
				{5, {0, 3, 7, 3, 0, 0, 0, 0}},
				
				// Diminished Triad arpeggio, root note: C, up-down
				{6, {0, 3, 6, 0, 3, 6, 0, 0}},
				
				// Augmented Triad arpeggio, root note: C, up-down
				{5, {0, 4, 8, 4, 0, 0, 0, 0}},
				
				// Major seventh arpeggio, root note: C, up, up (+1 octave)
				{7, {0, 4, 7, 11, 7, 4, 0, 0}},
				
				// Dominant Seventh Arpeggios, root note: C, up, up (+1 octave)
				{8, {0, 4, 7, 10, 0, 4, 7, 10}},
				
				// Minor Seventh arpeggio, root note: C, up, up (+1 octave)
				{8, {0, 3, 7, 10, 12, 15, 19, 22}},				
				
				// Halfed-dimished Seventh Arpeggios, root note: C, up, up (+1 octave)
				{7, {0, 3, 6, 10, 6, 3, 0, 0}}
			}};
			
			// But we also want these sequences to be modified in real time by the user,
			// whithout change the initial sequence, so we have another copy of the previous
			// 8 sequences, that the user can modify.
			// In this way, the default sequences are never altered.
			std::array<NoteSequence, 8> userNoteSequences =
			{{
				// Major Triad arpeggio, root note: C, up-down // -5
				// Default sequence, no specific arpeggio/mellody
				{8, {0, 0, 0, 0, 0, 0, 0, 0}},
				
				// Minor Triad arpeggio,  root note: C, up-down
				{5, {0, 3, 7, 3, 0, 0, 0, 0}},
				
				// Diminished Triad arpeggio, root note: C, up-down
				{6, {0, 3, 6, 0, 3, 6, 0, 0}},
				
				// Augmented Triad arpeggio, root note: C, up-down
				{5, {0, 4, 8, 4, 0, 0, 0, 0}},
				
				// Major seventh arpeggio, root note: C, up, up (+1 octave)
				{7, {0, 4, 7, 11, 7, 4, 0, 0}},
				
				// Dominant Seventh Arpeggios, root note: C, up, up (+1 octave)
				{8, {0, 4, 7, 10, 0, 4, 7, 10}},
				
				// Minor Seventh arpeggio, root note: C, up, up (+1 octave)
				{8, {0, 3, 7, 10, 12, 15, 19, 22}},				
				
				// Halfed-dimished Seventh Arpeggios, root note: C, up, up (+1 octave)
				{7, {0, 3, 6, 10, 6, 3, 0, 0}}
			}};
			
		public:
			NoteSequenceFactory();
			
			std::array<int, NoteSequenceFactory::MAX_STEP_COUNT> getSequence(int index);
			int getSequenceNumberOfSteps(int index);
	};
}

#endif
