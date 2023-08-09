//configuration stuff goes here

#pragma once

#include <DShotRMT.h>

//ammo counter
//voltage+ pin for the reciever diode (not absolutely needed, but saves power as it is only set ON when it is time to read)
#define IR_REC_POWER 32
//other side of the diode, measures IR light level
#define IR_REC_READBACK 35
//IR emitter LED, not absolutely needed, but it saves wear on the LED and battery if used
#define IR_EMITTER 33


//outputs
#define SOLENOID 25 // (HIGH=ON)
#define BUZZER 4 // (HIGH=ON)

//ESCS

#define ESC_TYPE_BRUSHED 1
#define ESC_TYPE_PWM 2
#define ESC_TYPE_DSHOT 3

//use the defines above to define this
#define ESC_TYPE ESC_TYPE_DSHOT

//delay in milliseconds between 0 and full before the motor is considered "at speed"
//if ESC_DSHOT_BIDIR is set to true, then this value is ignored
#define ESC_REV_DELAY 0

//only have the option for this if we have the dshot type
#if ESC_TYPE == ESC_TYPE_DSHOT
    #define ESC_DSHOT_MODE DSHOT300
    #define ESC_DSHOT_BIDIR false
#endif


//esc pinouts
#define ESC_1 18
#define ESC_2 23

//#define FOUR_ESCS
#ifdef FOUR_ESCS
    #define ESC_3
    #define ESC_4
#endif



//buttons
//all buttons will use internal pullup resistors by default

//debounce time in ms
#define DEBOUNCE_TIME 10

//the pin that this element occupies
#define TRIGGER 34
//if normally closed, set this to true, if normally open, set to false
#define TRIGGER_NC false

#define MAG_TRIG 27
#define MAG_TRIG_NC false

//do we have a rev trigger in the mix? if yes, we change the way some rev behavior works
//TODO: implement this.
//#define USE_REV_TRIG
#ifdef USE_REV_TRIG
  #define REV_TRIG 25
  #define REV_TRIG_NC false
#endif

//preset buttons
#define PRESET_A 14
#define PRESET_A_NC false

#define PRESET_B 27
#define PRESET_B_NC false

#define PRESET_C 26
#define PRESET_C_NC false

//encoder pins for the UI interraction
#define ENCODER_A 2
#define ENCODER_B 15

#define ENCODER_BUTTON 13
#define ENCODER_BUTTON_NC false


//display
#define I2C_SDA 19
#define I2C_SCL 22 //for the lolin32, this is also the external LED (LOW = ON with this)
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

//setup i2c display, see https://github.com/olikraus/u8g2/wiki/u8g2setupcpp for a list of proper constructors
//currently, this sets up a generic 128x64 display on the hardware i2c BUS
#include <U8g2lib.h>
#define INIT_CLASS U8G2_SSD1306_128X64_NONAME_1_HW_I2C


#define DEBUG_BAUD_RATE 9600
