#ifndef SYNTH80S_SRC_RPI_UI_POTENTIOMETER_H

#define SYNTH80S_SRC_RPI_UI_POTENTIOMETER_H

#include <wiringPi.h>
#include <mcp3004.h>

#include "../../utils/math-util.h"

#include <iostream>
#include <cmath>

namespace synth80s
{
	enum AdcChip
	{
		ADC0 = 0,
		ADC1 = 1
	};
	
    class Potentiometer
    {
        private:
            float minValue = 0.0f;
            float maxValue = 1.0f;
            float currentValue = 0.5f;
            float step = 0.1f;
            int potentiometerUnitsPerStep = 0;
            bool isActive = true;
            
            int previousPotentiometerReading = 0;
            int currentPotentiometerReading = 0;

            int wiringPiVirtualPinBase = 100;
            int virtualPinNumber = 100;

        public:
            Potentiometer(AdcChip adcChip, int pinNumber,
                            float minValue, float maxValue, float initialValue, float step);
            float readValue();
            bool isReadValueDifferent();
            void deactivate();
            void activate();
            
			static void initPotentiometersADC();
    };
}

#endif
