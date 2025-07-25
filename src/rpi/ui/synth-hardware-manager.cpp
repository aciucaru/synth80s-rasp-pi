#include "synth-hardware-manager.h"

namespace synth80s
{
    SynthHardwareManager::SynthHardwareManager()
    {
        /* Initialize WiringPi with WiringPi numbering scheme.
         * The initialization has to be made before we instantiate
         * any hardware-related objects (buttons, potentiometers, etc.) ! */
        wiringPiSetup();
        
        this->synthParamModeButton = new Button(23); // WiringPI numbering: pin 23 is RPi pin 13
        this->sequencerNoteFreqModeButton = new Button(24); // WiringPI numbering: pin 24 is RPi pin 19
        
        this->displayOnButton = new Button(28); // WiringPI numbering: pin 28 is RPi pin 20
        this->displayOffButton = new Button(29); // WiringPI numbering: pin 29 is RPi pin 21
        
		this->sequence1Button = new Button(0); // WiringPI numbering: pin 0 is RPi pin 17
		this->sequence2Button = new Button(2); // WiringPI numbering: pin 2 is RPi pin 27
		this->sequence3Button = new Button(3); // WiringPI numbering: pin 3 is RPi pin 22
		this->sequence4Button = new Button(25); // WiringPI numbering: pin 25 is RPi pin 26
		
		this->sequence5Button = new Button(4); // WiringPI numbering: pin 4 is RPi pin 23
		this->sequence6Button = new Button(5); // WiringPI numbering: pin 5 is RPi pin 24
		this->sequence7Button = new Button(6); // WiringPI numbering: pin 6 is RPi pin 25
		this->sequence8Button = new Button(27); // WiringPI numbering: pin 27 is RPi pin 16
        
        // Initialize ADCs for potentiometers, on ly after this function call
        // should we instantiate any potentiometer
        Potentiometer::initPotentiometersADC();

        this->synthOctavesOffsetPot = new Potentiometer(synth80s::ADC0, 7, -2, 2, 0, 1);
        this->synthSemitonesOffsetPot = new Potentiometer(synth80s::ADC0, 6, -12, 12, 0, 1);
        
        this->synthTriangleWeightPot = new Potentiometer(synth80s::ADC0, 5, 0.0f, 1.0f, 1.0f, 0.001f);
        this->synthSawtoothWeightPot = new Potentiometer(synth80s::ADC0, 4, 0.0f, 1.0f, 0.0f, 0.001f);
        this->synthSquareWeightPot = new Potentiometer(synth80s::ADC0, 3, 0.0f, 1.0f, 0.0f, 0.001f);
        
        this->synthUnisonDetunePot = new Potentiometer(synth80s::ADC0, 2, 0, 50, 0, 1);
        
        this->stepCountPot = new Potentiometer(synth80s::ADC1, 7, 1, 8, 8, 1);
        this->sequencerBPMPot = new Potentiometer(synth80s::ADC1, 6, 60, 300, 120, 1);
        
        this->synthGainPot = new Potentiometer(synth80s::ADC1, 5, 0.0f, 3.0f, 1.0f, 0.01f);

        Potentiometer* step1Pot = new Potentiometer(synth80s::ADC0, 7, -12.0f, 12.0f, 0.0f, 1.0f);
        Potentiometer* step2Pot = new Potentiometer(synth80s::ADC0, 6, -12.0f, 12.0f, 0.0f, 1.0f);
        Potentiometer* step3Pot = new Potentiometer(synth80s::ADC0, 5, -12.0f, 12.0f, 0.0f, 1.0f);
        Potentiometer* step4Pot = new Potentiometer(synth80s::ADC0, 4, -12.0f, 12.0f, 0.0f, 1.0f);

        Potentiometer* step5Pot = new Potentiometer(synth80s::ADC0, 3, -12.0f, 12.0f, 0.0f, 1.0f);
        Potentiometer* step6Pot = new Potentiometer(synth80s::ADC0, 2, -12.0f, 12.0f, 0.0f, 1.0f);
        Potentiometer* step7Pot = new Potentiometer(synth80s::ADC0, 1, -12.0f, 12.0f, 0.0f, 1.0f);
        Potentiometer* step8Pot = new Potentiometer(synth80s::ADC0, 0, -12.0f, 12.0f, 0.0f, 1.0f);

        this->stepSemitonesOffsetPotArray.push_back(step1Pot);
        this->stepSemitonesOffsetPotArray.push_back(step2Pot);
        this->stepSemitonesOffsetPotArray.push_back(step3Pot);
        this->stepSemitonesOffsetPotArray.push_back(step4Pot);

        this->stepSemitonesOffsetPotArray.push_back(step5Pot);
        this->stepSemitonesOffsetPotArray.push_back(step6Pot);
        this->stepSemitonesOffsetPotArray.push_back(step7Pot);
        this->stepSemitonesOffsetPotArray.push_back(step8Pot);
    }

    int SynthHardwareManager::readOctavesOffset()
    {
		const int octavesOffset = static_cast<int>(this->synthOctavesOffsetPot->readValue());
		
		if (this->paramMode == READ_SYNTH_PARAMS &&
			this->isDisplayEnabled == true &&
			this->synthOctavesOffsetPot->isReadValueDifferent())
				this->display.printParam("OCTAVES", octavesOffset);
			
		return octavesOffset;
    }

    int SynthHardwareManager::readSemitonesOffset()
    {

		const int semitonesOffset = static_cast<int>(this->synthSemitonesOffsetPot->readValue());
		
		if (this->paramMode == READ_SYNTH_PARAMS &&
			this->isDisplayEnabled == true &&
			this->synthSemitonesOffsetPot->isReadValueDifferent())
				this->display.printParam("SEMITONES", semitonesOffset);
			
		return semitonesOffset;
    }

    float SynthHardwareManager::readTriangleWeight()
    {
		const float triangleWeight = this->synthTriangleWeightPot->readValue();
		
		if (this->paramMode == READ_SYNTH_PARAMS &&
			this->isDisplayEnabled == true &&
			this->synthTriangleWeightPot->isReadValueDifferent())
				this->display.printParam("TRIANGLE", triangleWeight);
			
		return triangleWeight;
    }
    
    float SynthHardwareManager::readSawtoothWeight()
    {
		const float sawtoothWeight = this->synthSawtoothWeightPot->readValue();
		
		if (this->paramMode == READ_SYNTH_PARAMS &&
			this->isDisplayEnabled == true &&
			this->synthSawtoothWeightPot->isReadValueDifferent())
				this->display.printParam("SAWTOOTH", sawtoothWeight);
			
		return sawtoothWeight;
    }
    
    float SynthHardwareManager::readSquareWeight()
    {
		const float synthSquareWeight = this->synthSquareWeightPot->readValue();
		
		if (this->paramMode == READ_SYNTH_PARAMS &&
			this->isDisplayEnabled == true &&
			this->synthSquareWeightPot->isReadValueDifferent())
				this->display.printParam("SQUARE", synthSquareWeight);
			
		return synthSquareWeight;
    }

    int SynthHardwareManager::readUnisonDetune()
    {
		const float synthUnisonDetune = static_cast<int>(this->synthUnisonDetunePot->readValue());
				
		if (this->paramMode == READ_SYNTH_PARAMS &&
			this->isDisplayEnabled == true &&
			this->synthUnisonDetunePot->isReadValueDifferent())
				this->display.printParam("UNISON", synthUnisonDetune);
			
		return synthUnisonDetune;
	}

    int SynthHardwareManager::readStepCount()
    {
		const int stepCount = static_cast<int>(this->stepCountPot->readValue());
		
		return stepCount;
	}
    
    int SynthHardwareManager::readSequencerBPM()
    {
		const int bpm = static_cast<int>(this->sequencerBPMPot->readValue());
		
		if (this->isDisplayEnabled == true &&
			this->sequencerBPMPot->isReadValueDifferent())
				this->display.printParam("TEMPO", bpm);
				
		return bpm;
	}

    float SynthHardwareManager::readGain()
    {
        const float gain = this->synthGainPot->readValue();
        
        if (this->isDisplayEnabled == true &&
			this->synthGainPot->isReadValueDifferent())
				this->display.printParam("VOLUME", gain);
				
		return gain;
    }

    int SynthHardwareManager::readStepSemitonesOffset(int stepIndex)
	{
		const int stepSemitonesOffset = static_cast<int>(this->stepSemitonesOffsetPotArray.at(stepIndex)->readValue());
		
		if (this->paramMode == READ_STEP_FREQ &&
			this->isDisplayEnabled == true &&
			this->stepSemitonesOffsetPotArray.at(stepIndex)->isReadValueDifferent())
				this->display.printParam("STEP St", stepSemitonesOffset);
		
		return stepSemitonesOffset;
    }
    
    int SynthHardwareManager::readSequenceIndex()
    {
		// If a button has been pressed we store the corresponding index
		// into the 'selectedSequence' class property
		if (this->sequence1Button->readValue() == true)
			this->selectedSequence = 0;
			
		else if (this->sequence2Button->readValue() == true)
			this->selectedSequence = 1;
			
		else if (this->sequence3Button->readValue() == true)
			this->selectedSequence = 2;
			
		else if (this->sequence4Button->readValue() == true)
			this->selectedSequence = 3;
			
		else if (this->sequence5Button->readValue() == true)
			this->selectedSequence = 4;
			
		else if (this->sequence6Button->readValue() == true)
			this->selectedSequence = 5;
			
		else if (this->sequence7Button->readValue() == true)
			this->selectedSequence = 6;
					
		else if (this->sequence8Button->readValue() == true)
			this->selectedSequence = 7;
		
		return this->selectedSequence;
	} 
    
    void SynthHardwareManager::readParamMode()
    {
		const bool SYNTH_MODE = this->synthParamModeButton->readValue();
		const bool STEP_FREQ_MODE = this->sequencerNoteFreqModeButton->readValue();
		
		if (SYNTH_MODE == true)
		{
            // Potentiometers for synthesizer
			this->paramMode = READ_SYNTH_PARAMS;
			
			this->synthOctavesOffsetPot->activate();
            this->synthSemitonesOffsetPot->activate();
            
            this->synthTriangleWeightPot->activate();
            this->synthSawtoothWeightPot->activate();
            this->synthSquareWeightPot->activate();
            
            this->synthUnisonDetunePot->activate();
            
            // Potentiometers for step notes frequencies
            for (auto &potentiometer : this->stepSemitonesOffsetPotArray)
            {
				potentiometer->deactivate();
			}
		}
		
		if (STEP_FREQ_MODE == true)
		{
			this->paramMode = READ_STEP_FREQ;
			
			// Potentiometers for synthesizer
			this->paramMode = READ_SYNTH_PARAMS;
			
			this->synthOctavesOffsetPot->deactivate();
            this->synthSemitonesOffsetPot->deactivate();
            
            this->synthTriangleWeightPot->deactivate();
            this->synthSawtoothWeightPot->deactivate();
            this->synthSquareWeightPot->deactivate();
            
            this->synthUnisonDetunePot->deactivate();
            
            // Potentiometers for step notes frequencies
            for (auto &potentiometer : this->stepSemitonesOffsetPotArray)
            {
				potentiometer->activate();
			}
		}
	}
	
	void SynthHardwareManager::readIfDisplayEnabled()
    {
		const bool IS_ON_BUTTON_PRESSED = this->displayOnButton->readValue();
		const bool IS_OFF_BUTTON_PRESSED = this->displayOffButton->readValue();
		
		if (IS_ON_BUTTON_PRESSED)
			this->isDisplayEnabled = true;
			
		if (IS_OFF_BUTTON_PRESSED)
			this->isDisplayEnabled = false;
			
		// std::cout << "display enabled: " << this->isDisplayEnabled << std::endl;
	}
	
	void SynthHardwareManager::updateDisplay()
    {
		if (this->isDisplayEnabled)
			this->display.update();
	}
}
