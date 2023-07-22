
#pragma once

#include <Arduino.h>

#include "Configuration.h"

int loopItem(int item, int min, int max);


void drawDialGauge(INIT_CLASS *miniDisp, short x, short y, short radius, int min, int max, int val);
void drawBarGauge(INIT_CLASS *miniDisp, bool isHorizontal, short x, short y, short width, short height, int min, int max, int val);
bool putMenu(INIT_CLASS *miniDisp, int* selectedItem, const char** menuList, int entryCount);
