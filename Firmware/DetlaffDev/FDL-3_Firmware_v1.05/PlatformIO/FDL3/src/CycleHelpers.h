#pragma once

#include <Arduino.h>


extern unsigned long logicLastCheck;
extern unsigned long logicSwitchCheck;
extern int clickCount;
extern int hitCount;

void cycleShutdown();
void shutdownFwAndPush();
void spinDownFW(bool resetCheckTimer);
bool checkCount();
void triggerLogic(bool &triggerState, byte &shotsCached);
bool enterFireLoop(byte shotsCached);
bool enterAutoLoop(byte shotsCached);
bool inFullAuto();
boolean triggerDown();
boolean lockOn();
int presetButtonDown();
int pusherSwitchDown();
int readESCPower();
void setFwSpeed(int newSpeed);
int getSpinupByMotorSpeed();
double doubleMap(double x, double in_min, double in_max, double out_min, double out_max);
byte getBurstCount();
int getROF();





