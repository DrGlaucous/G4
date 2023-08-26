#pragma once



#include <Arduino.h>

#include "main.h"
#include "configuration.h"

//the menu library
#include <GEM_u8g2.h>


class menuHandler
{
    public:
    menuHandler();
    void start();

    void update();

    private:
	//functions

	bool handleNav(); //process button input and navegate menu

    void screenDrawLoop(int value);



    //vars

    //for drawing pages outside a do-while loop
    bool drawing_screen = false;
    bool first_page = false;

    //display class
    INIT_CLASS u8g2;



    ////////////////////////////////TEST
    unsigned int deltaMillis = 0;
    bool virtualIn = false;

    int number = 0;
    bool enablePrint = false;

    GEMItem menuItemInt;
    GEMItem menuItemBool;
    GEMItem menuItemButton;
    GEMPage menuPageMain;
    GEM_u8g2 menu;



};
