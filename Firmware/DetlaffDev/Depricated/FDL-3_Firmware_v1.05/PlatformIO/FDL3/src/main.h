#pragma once

#include <MicroView.h>
#include <Encoder.h>
#include <EEPROM.h>
#include <Servo.h>
#include "config.h"

struct StaticSettings {
  byte btnMode;
  int brightness;
  byte soundOn;
  int batOffset;
  int brkAgr;
  int usrLock;
  int minSpeed;
  int maxSpeed;
};

struct BlastSettings {
  int speedValue;
  int rofValue;
  byte burstCount;
  int minSpinup;
  int maxSpinup;
  int spinDown; //units per ms for single value drop (higher = slower)
  int idleTime;
  byte fireMode;  
};


extern const byte versionNumber;
extern const String splashText; //can be two lines split with space

extern Servo flywheelESC; 
extern Encoder myEnc;
extern MicroViewWidget *mainGauge;
extern MicroViewWidget *voltMeter;

extern byte knobMenuIndex;
extern byte presetMenuIndex;
extern const char *knobMenu[];
extern const char *burstMenu[];
extern const char *soundMenu[];
extern const char *presetMenu[];
extern const char *btnmodeMenu[];
extern const char *firemodeMenu[];


extern bool liveKnobScrollMode;
extern bool menuBtnWasDown;
extern bool firstMenuRun;
extern bool speedLocked;
extern bool firstRun;
extern unsigned long lastSpinCheck;
extern unsigned long lastSettingsSave;
extern unsigned long lastBatAlarm;
extern unsigned long brakeRelease;
extern unsigned long idleRelease;
extern long encoderChange;
extern int currentSpeed;
extern int spindownTarget;

extern float batteryCheck[batteryCheckLength];
extern unsigned long lastBatteryCheck;
extern int batteryCheckIndex;
extern float batteryCheckSum;


extern MicroViewWidget *mainGauge;
extern MicroViewWidget *voltMeter;


extern StaticSettings currStSettings;
extern StaticSettings lastStSettings;
extern StaticSettings defStSettings;

extern BlastSettings currBlSettings;
extern BlastSettings lastBlSettings;
extern BlastSettings readBlSettings;
extern BlastSettings defBlSettings;
