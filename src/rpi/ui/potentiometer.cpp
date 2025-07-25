#include "potentiometer.h"

namespace synth80s
{
    Potentiometer::Potentiometer(AdcChip adcChip, int pinNumber,
                                    float minValue, float maxValue, float initialValue,
                                    float step)
                    : wiringPiVirtualPinBase(wiringPiVirtualPinBase),
                        minValue(minValue),
                        maxValue(maxValue),
                        currentValue(initialValue),
                        step(step)
    {
		if (adcChip == ADC0)
			this->virtualPinNumber = 100 + pinNumber;
		else
			this->virtualPinNumber = 200 + pinNumber;
			
		// how many steps are between minValue and maxValue
		const int totalSteps = static_cast<int>(std::floor((this->maxValue - this->minValue) / this->step) + 1);
		
		this->potentiometerUnitsPerStep = static_cast<int> (1023.0f / (totalSteps - 1));
		
		std::cout << "min: " << this->minValue << ", max: " << this->maxValue << ", steps: " << totalSteps << ", units: " << this->potentiometerUnitsPerStep << std::endl;
    }

    float Potentiometer::readValue()
    {
		if (this->isActive)
		{
			const int POT_VALUE = analogRead(this->virtualPinNumber);

			// The MPC3008 has 10 bit precission, so the potentiometer will be read as values btween 0 and 1023
			// Find the the value mapped from (0, 1023) to (minValue, maxValue)
			const float MAPPED_VALUE = (POT_VALUE * (this->maxValue - this->minValue) ) / 1023.0f + this->minValue;

			// Find out how many integer steps correspond to the mapped value
			const int NUMBER_OF_STEPS = static_cast<int>( lround((MAPPED_VALUE - this->minValue) / this->step) );
			
			// Before updating, store the current reading from the potentiometer in the last reading
			this->previousPotentiometerReading = this->currentPotentiometerReading;
			
			// Update current potentiometer reading
			this->currentPotentiometerReading = POT_VALUE;
			
			// Recompute value, so it haves an integer multiple of 'step' value
			this->currentValue = this->minValue + this->step * NUMBER_OF_STEPS;
			
			return this->currentValue;
		}
		// else don't read from the potentiometer, just return the last read value
		else
		{
			// Before updating, store the current reading from the potentiometer in the last reading
			this->previousPotentiometerReading = this->currentPotentiometerReading;
			
			return this->currentValue;
		}
    }
    
	bool Potentiometer::isReadValueDifferent()
	{
		if (this->potentiometerUnitsPerStep > 1)
		{
			if (std::abs(this->previousPotentiometerReading - this->currentPotentiometerReading) >= this->potentiometerUnitsPerStep)
				return true;
			else
				return false;
		}
		else
		{
			const int TRESHOLD = 10;
			if (std::abs(this->previousPotentiometerReading - this->currentPotentiometerReading) >= TRESHOLD)
				return true;
			else
				return false;
		}
	}
	
	void Potentiometer::deactivate()
	{
		this->isActive = false;
	}
	
	void Potentiometer::activate()
	{
		this->isActive = true;
	}
    
    void Potentiometer::initPotentiometersADC()
    {
        std::cout << "Potentiometers ADC intialized" << std::endl;

        const int CHIP1_VIRTUAL_PIN_BASE = 100;
        const int CHIP2_VIRTUAL_PIN_BASE = 200;

        const int SPI_CHANNEL0 = 0;
        const int SPI_CHANNEL1 = 1;

        // Initialize both MCP3008 chips that are used in this project.
        // Each chip has a virtual pin base, which is the number from which the pin numbers
        // start from.
        mcp3004Setup(CHIP1_VIRTUAL_PIN_BASE, SPI_CHANNEL0);
        mcp3004Setup(CHIP2_VIRTUAL_PIN_BASE, SPI_CHANNEL1);
    }
}
