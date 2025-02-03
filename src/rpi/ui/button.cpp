#include "button.h"

namespace synth80s
{
    Button::Button(int pinNumber)
    : pinNumber(pinNumber)
    {
        pinMode(pinNumber, INPUT);
        pullUpDnControl(pinNumber, PUD_DOWN);
    }

    bool Button::readValue()
    {
        const int BUTTON_VALUE = digitalRead(this->pinNumber);
        
        if (BUTTON_VALUE == HIGH)
			this->currentValue = true;
		else
			this->currentValue = false;
			
		return this->currentValue;
    }
    
    bool Button::getLastValue() { return this->currentValue; }
}
