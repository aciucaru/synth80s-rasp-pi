#ifndef SYNTH80S_SRC_RPI_UI_SYNTH_HARDWARE_MANAGER_H

#define SYNTH80S_SRC_RPI_UI_SYNTH_HARDWARE_MANAGER_H

#include "button.h"
#include "potentiometer.h"
#include "display.h"

#include <wiringPi.h>

#include <iostream>
#include <cmath>
#include <vector>

namespace synth80s
{
	/* Enum that tells the parameter reader in what mode it is.
	 * If it's in 'READ_SYNTH_PARAMS' mode, then the values from the potentiometers
	 * are used for reading synth parameters values.
	 * If the mode is 'READ_STEP_FREQ', then the values from the potentiometers
	 * are used to read the frequencies (note semitones) of the notes of the step
	 * sequencer. */
	enum ReaderMode
	{
		READ_SYNTH_PARAMS = 1,
		READ_STEP_FREQ = 2
	};
	
    class SynthHardwareManager
    {
        private:
			ReaderMode paramMode = READ_SYNTH_PARAMS;
			
			/*    Note: C++ does not have static initialzer blocks like Java,
			 * so we cannot call any code before the constructor.
			 *    But we also need to call the wiringPiSetup() function
			 * before we instantiate any buttons, potentiometers, etc.
			 *    This is why the hardware-related instances of this class
			 * are pointers and are dinamically allocated, because we need
			 * wiringPiSetup() function to run before the constructor
			 * initializer list, which is not possible, so this is why we
             * don't use intializaer list and we dynamically instantiate
             * most of the hardware-related properties of this class. */
			 
			// These buttons set the mode to either 'READ_SYNTH_PARAMS'
			// or to 'READ_STEP_FREQ'
            Button* synthParamModeButton;
            Button* sequencerNoteFreqModeButton;
            
            // These buttons turn the display on/off
            Button* displayOnButton;
            Button* displayOffButton;
            
            // These buttons select one sequence from 8 possible sequences
            Button* sequence1Button;
            Button* sequence2Button;
            Button* sequence3Button;
            Button* sequence4Button;
            
            Button* sequence5Button;
            Button* sequence6Button;
            Button* sequence7Button;
            Button* sequence8Button;
            
            // This property stores the value selected by one of the previous buttons
            int selectedSequence = 0;

            // Potentiometers for synth parameters
            Potentiometer* synthOctavesOffsetPot;
            Potentiometer* synthSemitonesOffsetPot;
            
            Potentiometer* synthTriangleWeightPot;
            Potentiometer* synthSawtoothWeightPot;
            Potentiometer* synthSquareWeightPot;
            
            Potentiometer* synthUnisonDetunePot;
            
            // Potentiometer for number of steps (notes)
            Potentiometer* stepCountPot;
            
            // Potentiometer for sequencer BPM (tempo)
            Potentiometer* sequencerBPMPot;
            
            // Potentiometers for step notes frequencies
            std::vector<Potentiometer*> stepSemitonesOffsetPotArray;
            
            // Potentiometer for volume
            Potentiometer* synthGainPot;
            
            // The display that shows the current value of a parameter, as
            // that value changes in time.
            // This does not depend on the wiringPi library, so it can be
            // statically allocated.
            Display display;
            
            bool isDisplayEnabled = false;
            
        public:
            SynthHardwareManager();

            int readOctavesOffset();
            int readSemitonesOffset();
            
            float readTriangleWeight();
            float readSawtoothWeight();
            float readSquareWeight();
            
            int readUnisonDetune();
            
            int readStepCount();
            int readSequencerBPM();
            
            float readGain(); // the volume of the synth

            int readStepSemitonesOffset(int stepIndex);
            
            // Reads the selected note sequence to be played
            int readSequenceIndex(); 
            
            void readParamMode();
            void readIfDisplayEnabled();
            
            void updateDisplay();
    };
}

#endif
