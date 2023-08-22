
// #include <Arduino.h>

// #include "main.h"
// #include "configuration.h"
// #include "display.h"

// //the menu library
// //#include <menu.h>
// //#include <menuIO/u8g2Out.h>
// //#include <menuIO/encoderIn.h>
// //#include <menuIO/softKeyIn.h>

// //#include <menuIO/stringIn.h> //general-purpose input stream

// //#include <menuIO/keyIn.h>
// //#include <menuIO/chainStream.h>
// //#include <menuIO/serialOut.h>
// //#include <menuIO/serialIn.h>

// using namespace Menu;


// // define menu colors --------------------------------------------------------
// //each color is in the format:
// //  {{disabled normal,disabled selected},{enabled normal,enabled selected, enabled editing}}
// // this is a monochromatic color table
// const colorDef<uint8_t> colors[6] MEMMODE={
//   {{0,0},{0,1,1}},//bgColor
//   {{1,1},{1,0,0}},//fgColor
//   {{1,1},{1,0,0}},//valColor
//   {{1,1},{1,0,0}},//unitColor
//   {{0,1},{0,0,1}},//cursorColor
//   {{1,1},{1,0,0}},//titleColor
// };


// ////////////////////////////////TEST
// unsigned int deltaMillis = 0;
// bool virtualIn = false;

// //vars
// stringIn<IN_BUF_SIZE> str_in; //anything as an input
// //using nav.doNav(cmd) doesn't allow us to process multiple events happening in the same tick
// //lcd display
// INIT_CLASS u8g2 = INIT_CLASS(U8G2_R0, U8X8_PIN_NONE , I2C_SCL, I2C_SDA);

// //TEST MENU SELECTION VARS
// int selTest=0;
// int chooseTest=-1;
// uint16_t hrs=0;
// uint16_t mins=0;
// char buf1[5]="0x11";
// int test=55;
// int ledCtrl=HIGH;




// /////////////////////////
// /////////////////////////
// /////////////////////////
// /////////////////////////
// TOGGLE(ledCtrl,setLed,"Led: ",doNothing,noEvent,noStyle//,doExit,enterEvent,noStyle
// ,VALUE("On",HIGH,doNothing,noEvent)
// ,VALUE("Off",LOW,doNothing,noEvent)
// );
// SELECT(selTest,selMenu,"Select",doNothing,noEvent,noStyle
// ,VALUE("Zero",0,doNothing,noEvent)
// ,VALUE("One",1,doNothing,noEvent)
// ,VALUE("Two",2,doNothing,noEvent)
// );
// CHOOSE(chooseTest,chooseMenu,"Choose",doNothing,noEvent,noStyle
// ,VALUE("First",1,doNothing,noEvent)
// ,VALUE("Second",2,doNothing,noEvent)
// ,VALUE("Third",3,doNothing,noEvent)
// ,VALUE("Last",-1,doNothing,noEvent)
// );
// MENU(subMenu,"Sub-Menu",doNothing,noEvent,noStyle
// ,OP("Sub1",doNothing,noEvent)
// // ,altOP(altPrompt,"",doNothing,noEvent)
// ,EXIT("<Back")
// );
// altMENU(menu,timeMenu,"Time",doNothing,noEvent,noStyle,(systemStyles)(_asPad|Menu::_menuData|Menu::_canNav|_parentDraw)
// ,FIELD(hrs,"",":",0,11,1,0,doNothing,noEvent,noStyle)
// ,FIELD(mins,"","",0,59,10,1,doNothing,noEvent,wrapStyle)
// );

// const char* constMEM hexDigit MEMMODE="0123456789ABCDEF";
// const char* constMEM hexNr[] MEMMODE={"0","x",hexDigit,hexDigit};
// MENU(mainMenu,"Main menu",doNothing,noEvent,wrapStyle
// ,OP("Op1",doNothing,noEvent)
// ,OP("Op2",doNothing,noEvent)
// //,FIELD(test,"Test","%",0,100,10,1,doNothing,noEvent,wrapStyle)
// ,SUBMENU(timeMenu)
// ,SUBMENU(subMenu)
// ,SUBMENU(setLed)
// ,SUBMENU(selMenu)
// ,SUBMENU(chooseMenu)
// ,EDIT("Hex",buf1,hexNr,doNothing,noEvent,noStyle)
// ,EXIT("<Exit")
// );

// MENU_INPUTS(in,&str_in);

// MENU_OUTPUTS(out,MAX_DEPTH
// ,U8G2_OUT(u8g2,colors,fontX,fontY,offsetX,offsetY,{0,0,U8_Width/fontX,U8_Height/fontY})
// ,NONE
// //,SERIAL_OUT(Serial)
// );

// NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);
// /////////////////////////
// /////////////////////////
// /////////////////////////
// /////////////////////////


// menuHandler::menuHandler()
// {
// 	u8g2.begin();
// }


// void menuHandler::update()
// {
// 	handleNav();

// }

// void menuHandler::handleNav()
// {
// 	//determine the direction we've rotated, so we know what navegation char to add to the buffer
// 	char navChar = 0;
// 	if(gPins.encoder_val < 0)
// 		navChar = '-';
// 	else
// 		navChar = '+';

// 	for(int i = 0; i < abs(gPins.encoder_val); ++i)
// 	{
// 		//highly unlikely this will happen, but we discard any extra inputs if it does
// 		if(i > IN_BUF_SIZE)
// 			break;

// 		str_in.write(navChar);
// 	}

// 	//write any selection events (str_in is a ring buffer, so if we have an overflow, this will overwrite something sent earlier)
// 	if(gPins.encoderSwitch.fell())
// 		str_in.write('*');

// }


// // const navCodesDef Menu::defaultNavCodes={
// //   {noCmd,(uint8_t)0xff},
// //   {escCmd,'/'},
// //   {enterCmd,'*'},
// //   {upCmd,'+'},
// //   {downCmd,'-'},
// //   {leftCmd,'-'},
// //   {rightCmd,'+'},
// //   {idxCmd,'?'},
// //   {scrlUpCmd,0x35},
// //   {scrlUpCmd,0x36}
// // };
