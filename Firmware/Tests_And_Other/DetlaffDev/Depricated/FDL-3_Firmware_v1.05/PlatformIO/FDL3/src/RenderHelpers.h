#pragma once

#include <Arduino.h>

void renderVoltMeter();
void batteryWarning();
void batteryCritical();
void renderLockIndicator();
void renderInfoMenu();
void renderUserLock();
void renderKnobScrollMenu();
void renderMenu(byte &menuIndex, const char label[], const char* menu[], byte arraySize);
void renderGauge(int &gaugeValue, String label, int gaugeMin, int gaugeMax, int valueMin, int valueMax, int detPerMove);
void renderSplash(String splashText);
void renderPresetMenu();
void renderPreset(byte preset);






