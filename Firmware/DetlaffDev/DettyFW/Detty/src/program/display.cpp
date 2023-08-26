
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
menuItemBool("Enable print:", enablePrint),
menuItemButton("Beep", beeper),
menuPageMain("Main Menu"),
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
		gBuzzer.beep_single(1);
	}


	//don't draw anything
	if(drawing_screen == false)
         return;

	if(first_page)
	{
		first_page = false;
		u8g2.firstPage();
		menu.drawMenu(true);
	}
	else if(u8g2.nextPage())
		menu.drawMenu(true);
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
	Serial.println(someUpdate);

	return someUpdate;
}







