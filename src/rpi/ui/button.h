#ifndef SYNTH80S_SRC_RPI_UI_BUTTON_H

#define SYNTH80S_SRC_RPI_UI_BUTTON_H

#include <wiringPi.h>

namespace synth80s
{
    class Button
    {
        private:
			bool currentValue = false;
            int pinNumber = -1;

        public:
            Button(int pinNumber);
            bool readValue();
            bool getLastValue();
    };
}

#endif
