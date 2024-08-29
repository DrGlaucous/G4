#pragma once

#include <Arduino.h>


void loadSettings();
void loadStaticSettings();
void writeStaticSettings();
bool staticSettingsChanged();
void loadCurrentSettings();
void writeCurrentSettings();
bool currentSettingsChanged();
void readPreset(byte presetIndex);
void writePreset(byte presetIndex);
void loadPreset(byte presetIndex);
void writeDefaultSettings();

