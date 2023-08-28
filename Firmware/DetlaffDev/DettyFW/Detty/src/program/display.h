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


    typedef struct callback_datapack_s
    {
        int* target;
        int value;
    } callback_datapack_t;
    //sets a flag that corresponds to the menu that should be entered
    static void handleCallback(callback_datapack_t inData);


    //vars

    //for drawing pages outside a do-while loop
    bool drawing_screen = false;
    bool first_page = false;

    int screen_type = 0;

    //display class
    INIT_CLASS u8g2;




    unsigned int deltaMillis = 0;
    bool virtualIn = false;

    int number = 0;
    bool enablePrint = false;

    GEMItem menuItemInt;
    GEMItem menuItemInt2;
    GEMItem menuItemInt3;
    GEMItem menuItemBool;
    GEMItem menuItemButton;
    GEMItem toSubMenA;
    GEMItem toSubMenB;

    GEMPage menuPageMain;
    GEMPage subMenA;
    GEMPage subMenB;
    GEM_u8g2 menu;



};
