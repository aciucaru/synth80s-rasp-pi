#ifndef SYNTH80S_SRC_RPI_UI_DISPLAY_H

#define SYNTH80S_SRC_RPI_UI_DISPLAY_H

#include <lgpio.h>
#include <string>
#include <iostream>
#include "../../../libs/SSD1306_OLED_RDL.hpp"

namespace synth80s
{
	class Display
	{
		private:
			// Settings for screen size
			static const int16_t DISPLAY_WIDTH = 128;
			static const int16_t DISPLAY_HEIGHT = 64;
			static const int FULLSCREEN_BUFFER_SIZE = Display::DISPLAY_WIDTH * Display::DISPLAY_HEIGHT / 8;
			
			// Define a buffer to cover whole screen
			uint8_t  screenBuffer[Display::FULLSCREEN_BUFFER_SIZE];
			
			// Settings for I2C
			static const int OLED_I2C_ADDRESS = 0x3C;
			static const int OLED_I2C_DEVICE = 1;
			static const int OLED_I2C_FLAGS = 0;
			
			// If this variable is false, any writing to the display will be ignored
			bool isProperlyInitialized = false;
			
			bool i2cDebug = false;
			
			// the OLED object
			SSD1306_RDL display;
			
		public:
			Display();
			~Display();
			
			// Main methods of this class: they print a line on the display
			void println(std::string& text);
			void printParam(const std::string& paramName, int numericValue);
			void printParam(const std::string& paramName, float numericValue);
			void update();
			
		private:
			bool init();
	};
}

#endif
