#include "note-sequence-factory.h"

namespace synth80s
{
    NoteSequenceFactory::NoteSequenceFactory()
    {

	}
	
	std::array<int, NoteSequenceFactory::MAX_STEP_COUNT> NoteSequenceFactory::getSequence(int index)
	{
		if (0 <= index && index < NoteSequenceFactory::MAX_STEP_COUNT)
		{
			// Copy the default step count into the user step count
			userNoteSequences[index].numberOfSteps = defaultNoteSequences[index].numberOfSteps;
			
			// Copy the default sequence into the user-editable sequence
			for (int i = 0; i < NoteSequenceFactory::MAX_STEP_COUNT; i++)
			{
				userNoteSequences[index].noteSequence[i] = defaultNoteSequences[index].noteSequence[i];
			}
			
			return this->userNoteSequences[index].noteSequence;
		}
		else
		{
			std::cout << "incorrect sequence: " << index << std::endl;
			
			// Copy the default step count into the user step count
			userNoteSequences[0].numberOfSteps = defaultNoteSequences[0].numberOfSteps;
			
			// Copy the default sequence into the user-editable sequence
			for (int i = 0; i < NoteSequenceFactory::MAX_STEP_COUNT; i++)
			{
				userNoteSequences[0].noteSequence[i] = defaultNoteSequences[0].noteSequence[i];
			}
			
			return this->userNoteSequences[index].noteSequence;
		}
	}
	
	int NoteSequenceFactory::getSequenceNumberOfSteps(int index)
	{
		if (0 <= index && index < NoteSequenceFactory::MAX_STEP_COUNT)
			return this->userNoteSequences[index].numberOfSteps;
		else
			return this->userNoteSequences[0].numberOfSteps;
	}
}
