#pragma once

//ammo counter
#define IR_REC_POWER 32
#define IR_REC_READBACK 35
#define IR_EMITTER 33

//outputs
#define SOLENOID 25 // (HIGH=ON)
#define BUZZER 4 // (HIGH=ON)
#define ESC_1
#define ESC_2


//buttons
#define TRIGGER 34
#define MAG_TRIG 27
#ifdef USE_REV_TRIG
  #define REV_TRIG 25
#endif

#define PRESET_A 14
#define PRESET_B 27
#define PRESET_C 26

#define ENCODER_A 2
#define ENCODER_B 15
#define ENCODER_BUTTON 13


//display
#define I2C_SDA 19
#define I2C_SCL 22 //this is also the external LED (LOW = ON with this)
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

//setup i2c display, see https://github.com/olikraus/u8g2/wiki/u8g2setupcpp for a list of proper constructors
#include <U8g2lib.h>
#define INIT_CLASS U8G2_SSD1306_128X64_NONAME_1_HW_I2C