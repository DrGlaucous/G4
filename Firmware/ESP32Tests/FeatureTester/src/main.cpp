#include <Arduino.h>
//#include <Wire.h>
#include <U8g2lib.h>

#include "Utils.h"
#include "Triangle.h"
#include "Configuration.h"
#include "UIElements.h"




//constructor defined in Configuration.h
INIT_CLASS u8g2(U8G2_R0, U8X8_PIN_NONE , I2C_SCL, I2C_SDA);




void setup() {

	InitTrigTbl();
	InitPins();
	Serial.begin(9600);
	
	//u8g2.setI2CAddress(0x3C);
	u8g2.begin();
}

void loop() {

	GetTicks();
	TickBuzzer();
	static int lastValue = 0;
	static int value = 0;
	int result = GetUserInput();
	
	value += result;



	const char* inputList[] =
	{
		"Apple",
		"Wheatley",
		"Wilson",
		"McQueen",
		"Speaker",
		"Beaker",
		"Pete",
	};

	putMenu(&u8g2, &value, inputList, 7);

	if(lastValue != value)
	{
		lastValue = value;
		Serial.println(value);
	}

	// value = loopItem(value, 0, 100);
	// if(lastValue != value)
	// {
	// 	Serial.println(value);

	// 	lastValue = value;

	// 	u8g2.firstPage();
	// 	do
	// 	{
	// 		//u8g2.setFont(u8g2_font_helvB12_tr);
	// 		//u8g2.drawStr(0,24,"Hello World!");
	// 		drawDialGauge(&u8g2, DISPLAY_HEIGHT/2, DISPLAY_HEIGHT/2, 24, 0, 100, value);
	// 		drawBarGauge(&u8g2, false, DISPLAY_WIDTH - 32, 4, 16, DISPLAY_HEIGHT - 8, 0, 100, value);
	// 	} while (u8g2.nextPage());
	// }
  



}


