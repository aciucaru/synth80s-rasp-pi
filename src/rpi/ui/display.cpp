#include "display.h"

namespace synth80s
{
	Display::Display()
	: display(Display::DISPLAY_WIDTH, Display::DISPLAY_HEIGHT)
	{
		// Attempt to initialize the I2C display and save the initialization result
		this->isProperlyInitialized = this->init();
	}
	
	Display::~Display()
	{
		// Switch off the display
		this->display.OLEDPowerDown();
		
		// Switch off I2C , optional may effect other programs & devices
		this->display.OLED_I2C_OFF();
	}
	
	bool Display::init()
	{
		std::cout << "OLED Test Begin" << std::endl;
		std::cout << "SSD1306 library Version Number: " << GetRDLibVersionNum() << std::endl;
		std::cout << "lgpio library Version Number: " << lguVersion() << std::endl;

		// Open  on I2C device
		if(this->display.OLED_I2C_ON(OLED_I2C_DEVICE, OLED_I2C_ADDRESS,OLED_I2C_FLAGS) != rpiDisplay_Success)
		{
			std::cout << "Error 1201:Cannot open I2C device bus" << std::endl;
			return false;
		}
		// Check if OLED on Bus
		if(this->display.OLEDCheckConnection() < 0)
		{
			std::cout << "Error 1202 : Cannot See Device on Bus" << std::endl;
			return false;
		}
		
		if (this->display.OLEDSetBufferPtr(Display::DISPLAY_WIDTH, Display::DISPLAY_HEIGHT, this->screenBuffer, sizeof(screenBuffer)) != rpiDisplay_Success)
			return false;
		this->display.OLEDclearBuffer();
		
		delayMilliSecRDL(500);
		this->display.OLEDbegin(this->i2cDebug); // initialize the OLED
		this->display.OLEDFillScreen(0xF0, 0); // splash screen bars, optional just for effect
		delayMilliSecRDL(1000);
		
		this->display.setFont(font_retro);
		this->display.setCursor(0, 0);
		
		return true;
	}
	
	void Display::println(std::string& text)
	{
		if (this->isProperlyInitialized)
		{
			this->display.OLEDclearBuffer();
			
			this->display.setCursor(0, 0);
			this->display.print(text);
			this->display.OLEDupdate();
			// delayMilliSecRDL(10);
		}
	}
	
	void Display::printParam(const std::string& paramName, int numericValue)
	{
		if (this->isProperlyInitialized)
		{
			this->display.OLEDclearBuffer();
			
			// Print parameter name
			this->display.setCursor(0, 0);
			this->display.print(paramName);
			
			// Print parameter value
			this->display.setCursor(0, 24);
			this->display.print(numericValue);
		}
	}
	
	void Display::printParam(const std::string& paramName, float numericValue)
	{
		if (this->isProperlyInitialized)
		{
			this->display.OLEDclearBuffer();
			
			// Print parameter name
			this->display.setCursor(0, 0);
			this->display.print(paramName);
			
			// Print parameter value
			this->display.setCursor(0, 24);
			this->display.print(numericValue);
		}
	}
	
	void Display::update()
	{
		this->display.OLEDupdate();
	}
}
