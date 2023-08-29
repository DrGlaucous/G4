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

    void screenDrawLoop(void);


    typedef struct callback_datapack_s
    {
        int* target;
        int value;
    } callback_datapack_t;
    //sets a flag that corresponds to the menu that should be entered
    static void handleCallback(callback_datapack_t inData);

    //enum list of things that can be drawn onscreen
    typedef enum display_list_e
    {
        DISPLAY_NULL, //draw nothing
        DISPLAY_MENU, //main navegation menu
        DISPLAY_FLYWHEEL_SPEED, //gauges n such
        DISPLAY_PUSH_RATE,
        DISPLAY_FLYWHEEL_RPM,
        DISPLAY_AMMO_COUNT,
        DISPLAY_FPS,
        DISPLAY_MAX,

    } display_list_t;


    //various draw utilities, specific gauges re-use these elements
    int loopItem(int item, int min, int max);
    static float map_float(float x, float in_min, float in_max, float out_min, float out_max);
    static void drawDialGauge(INIT_CLASS *miniDisp, short x, short y, short radius, int min, int max, int val);
    static void drawBarGauge(INIT_CLASS *miniDisp, bool isHorizontal, short x, short y, short width, short height, int min, int max, int val);

    void drawPowerGauge(INIT_CLASS *miniDisp, short x, short y);


    //vars

    //for drawing pages outside a do-while loop
    bool drawing_screen = true; //re-draw screen on init
    bool first_page = true;

    display_list_t screen_type = DISPLAY_NULL;

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
