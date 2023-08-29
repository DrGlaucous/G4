
#include <Arduino.h>

#include "main.h"
#include "configuration.h"
#include "display.h"

//the menu library
#include <GEM_u8g2.h>

//test function (function callbacks don't work if we refrence a non-static class funciton)
void beeper()
{
	gBuzzer.beep_multiple(50, 150, 5);
}

menuHandler::menuHandler(): u8g2(U8G2_R0, U8X8_PIN_NONE , I2C_SCL, I2C_SDA),
menuItemInt("Number:", number),
menuItemInt2("NUMA:", number),
menuItemInt3("NUMB:", number),
menuItemBool("Enable print:", enablePrint),
menuItemButton("Beep", beeper),
menuPageMain("Main Menu"),
subMenA("Menu A"),
subMenB("Menu B"),
toSubMenA("Sub A",subMenA),
toSubMenB("Sub B", subMenB),
menu(u8g2)
{

}

void menuHandler::start()
{
	u8g2.begin(); //led backend


	//start the menu library
	menu.setSplashDelay(0);
	menu.init();
	
	//add items to menu
	menuPageMain.addMenuItem(menuItemInt);
	menuPageMain.addMenuItem(menuItemBool);
	menuPageMain.addMenuItem(menuItemButton);
	menuPageMain.addMenuItem(toSubMenA);
	menuPageMain.addMenuItem(toSubMenB);

	subMenA.addMenuItem(menuItemInt);
	subMenA.addMenuItem(menuItemInt2);
	subMenA.setParentMenuPage(menuPageMain);

	subMenB.addMenuItem(menuItemBool);
	subMenB.addMenuItem(menuItemInt3);
	subMenB.addMenuItem(menuItemInt2);
	subMenB.addMenuItem(menuItemButton);
	subMenB.setParentMenuPage(menuPageMain);


	//add page to menu and set it as current
	menu.setMenuPageCurrent(menuPageMain);
	menu.drawMenu();

}


void menuHandler::update()
{
	if(handleNav())
	{
		drawing_screen = true;
		first_page = true;
		gBuzzer.beep_single(1000);
	}


	//don't draw anything
	if(drawing_screen == false)
         return;

	if(first_page)
	{
		first_page = false;
		u8g2.firstPage();
		screenDrawLoop();
	}
	else if(u8g2.nextPage())
		screenDrawLoop();
	else
		drawing_screen = false;

}



//#define GEM_KEY_NONE    0                         // No key presses are detected
//#define GEM_KEY_UP      U8X8_MSG_GPIO_MENU_UP     // Up key is pressed (navigate up through the menu items list, select next value of the digit/char of editable variable, or previous option in select)
//#define GEM_KEY_RIGHT   U8X8_MSG_GPIO_MENU_NEXT   // Right key is pressed (navigate through the link to another (child) menu page, select next digit/char of editable variable, execute code associated with button)
//#define GEM_KEY_DOWN    U8X8_MSG_GPIO_MENU_DOWN   // Down key is pressed (navigate down through the menu items list, select previous value of the digit/char of editable variable, or next option in select)
//#define GEM_KEY_LEFT    U8X8_MSG_GPIO_MENU_PREV   // Left key is pressed (navigate through the Back button to the previous menu page, select previous digit/char of editable variable)
//#define GEM_KEY_CANCEL  U8X8_MSG_GPIO_MENU_HOME   // Cancel key is pressed (navigate to the previous (parent) menu page, exit edit mode without saving the variable, exit context loop if allowed within context's settings)
//#define GEM_KEY_OK      U8X8_MSG_GPIO_MENU_SELECT // Ok/Apply key is pressed (toggle boolean menu item, enter edit mode of the associated non-boolean variable, exit edit mode with saving the variable, execute code associated with button)
bool menuHandler::handleNav()
{
	//determine the direction we've rotated, so we know what navegation char to add to the buffer
	bool someUpdate = (gPins.delta_encoder_val != 0);
	//for each one, update the menu quickly
	for(int i = 0; i < abs(gPins.delta_encoder_val); ++i)
	{
		if(menu.readyForKey())
		{
			if(gPins.delta_encoder_val < 0)
				menu.registerKeyPress(GEM_KEY_DOWN);
			else
				menu.registerKeyPress(GEM_KEY_UP);
		}
	}

	if(gPins.encoderSwitch.released())
	{
		someUpdate = true;
		if(menu.readyForKey())
		{
			menu.registerKeyPress(GEM_KEY_OK);
		}
	}

	return someUpdate;
}


void menuHandler::handleCallback(callback_datapack_t inData)
{
	*inData.target = inData.value;
}


//decide what to draw when it's actually time to do so
void menuHandler::screenDrawLoop(void)
{

	//switch statement controls what will be drawn, (for the code that controls what will be processed, look in handleNav)
	switch(screen_type)
	{
		default:
		case DISPLAY_NULL:
			drawPowerGauge(&u8g2, DISPLAY_WIDTH - 20, 0);
			break;
		case DISPLAY_MENU:
			menu.drawMenu(true);
			break;
		case DISPLAY_FLYWHEEL_SPEED: //SET the speed
			{
				//show power
				drawPowerGauge(&u8g2, DISPLAY_WIDTH - 20, 0);

				//show how fast we want the flywheels to spin
				drawDialGauge(&u8g2, DISPLAY_WIDTH / 2,
							DISPLAY_HEIGHT / 2,
							(DISPLAY_HEIGHT - 20) / 2,
							MIN_FLYWHEEL_SPEED,
							MAX_FLYWHEEL_SPEED,
							MAX_FLYWHEEL_SPEED / 2);

				break;
			}
		case DISPLAY_PUSH_RATE:
			{
				break;
			}
		case DISPLAY_FLYWHEEL_RPM: //SEE the speed (set it too)
			{
				break;
			}


	}




}

//loop input between min and max value (like over/underflows) min<=x<max
int menuHandler::loopItem(int item, int min, int max)
{
    //make it so that min = 0
    item -= min;
    max -= min;

    if(item >= max)
        item = (item % max); //0+...
    else if(item < 0)
        item = max + (item % max) - 1;

    return item + min;//add min back


    //if(*selectedItem >= entryCount)
    //    *selectedItem = (*selectedItem % entryCount); //0+...
    //else if(*selectedItem < 0)
    //    *selectedItem = entryCount + (*selectedItem % entryCount);

}

//the map function but it uses floats
float menuHandler::map_float(float x, float in_min, float in_max, float out_min, float out_max) {
    const float run = in_max - in_min;
    if(run == 0){
        log_e("map(): Invalid input range, min == max");
        return -1; // AVR returns -1, SAM returns 0
    }
    const float rise = out_max - out_min;
    const float delta = x - in_min;
    return (delta * rise) / run + out_min;
}

//draw a gauge centered on this coordinate
void menuHandler::drawDialGauge(INIT_CLASS *miniDisp, short x, short y, short radius, int min, int max, int val)
{

	unsigned char degree;
	short x1, y1, x2, y2, tx, ty;
	int i;


	//draw the edge ticks
	short tick_count = 7;
	for(i = 0; i < tick_count; ++i)
	{
		//192 because we want only 3/4 of the gauge to have ticks, +96 for orientation
		degree = 192/(tick_count - 1) * i + 96;

		//do the initial calculation for offset vars
		tx = (radius * gTrig.GetCos(degree)) / 512;
		ty = (radius * gTrig.GetSin(degree)) / 512;

		//apply offsets to coordinates
		x1 = x + tx*3/4;
		y1 = y + ty*3/4;
		x2 = x + tx;
		y2 = y + ty;

		miniDisp->drawLine(x1, y1, x2, y2);
	}
	//draw face
	miniDisp->drawCircle(x, y, radius, U8G2_DRAW_ALL);

	//draw knob
	degree = map(val, min, max, 0, 192) + 96;
	x2 = x + (radius * gTrig.GetCos(degree)) / 512;
	y2 = y + (radius * gTrig.GetSin(degree)) / 512;
	miniDisp->drawLine(x, y, x2, y2);



}

//draw a bar gauge with corner at this coordinate
void menuHandler::drawBarGauge(INIT_CLASS *miniDisp, bool isHorizontal, short x, short y, short width, short height, int min, int max, int val)
{
	
	miniDisp->drawFrame(x, y, width, height);

	//keep value within valid range
	if(val < min)
		val = min;
	else if(val > max)
		val = max;

	//how tall the "filled" box should be
	int fillHeight = map(val, min, max, 0, isHorizontal ? width : height);

	if(isHorizontal)
		miniDisp->drawBox(x, y, fillHeight, height);
	else
		miniDisp->drawBox(x, y + height - fillHeight, width, fillHeight);


}

//draw power HUD
void menuHandler::drawPowerGauge(INIT_CLASS *miniDisp, short x, short y)
{

	//TODO: move this somewhere where it WON't be re-calculated for each draw page
	//convert ADC number into a raw voltage and then step that up according to the voltage divider's values
	float volts = map_float(gPins.voltmeter_read, 0, ADC_VALUE_REF, 0, ADC_VOLTAGE_REF) *
					(R1_VAL + R2_VAL) / R2_VAL;


	short gaugeWidth = 8;
	short gaugeHeight = y - DISPLAY_HEIGHT - 8; //8 for font at the top

	//draw numeric voltage
	miniDisp->setFont(GEM_FONT_SMALL);
	char toBePrinted[10];
	sprintf(toBePrinted, "%.2f", volts);
	miniDisp->drawStr(x,y, toBePrinted);

	//testing voltmeter accuracy
	// Serial.print(gPins.voltmeter_read);
	// Serial.print("\t");
	// Serial.print(map_float(gPins.voltmeter_read, 0, ADC_VALUE_REF, 0, ADC_VOLTAGE_REF));
	// Serial.print("\t");
	// Serial.print(toBePrinted);
	// Serial.print("\t");
	// Serial.println(volts);


	//we need to do a second map here becuase the bar gauge only takes integers
	drawBarGauge(miniDisp, false,
				x + 20 - gaugeWidth, //4 * 5 pixels wide for the numer (4 wide font with 5 digits)
				y + 8, //for font at top
				gaugeWidth,
				gaugeHeight,
				0, 100, (int)map_float(volts, BATTERY_EMPTY, BATTERY_FULL_CHARGE, 0, 100));
}



