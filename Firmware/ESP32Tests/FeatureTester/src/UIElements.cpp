#include <Arduino.h>

#include "Configuration.h"
#include "Triangle.h"
#include "Utils.h"


//draw a gauge centered on this coordinate
void drawDialGauge(INIT_CLASS *miniDisp, short x, short y, short radius, int min, int max, int val)
{

	unsigned char degree;
	short x1, y1, x2, y2, tx, ty;
	int i;


	//draw the edge ticks
	short tick_count = 7;
	for(i = 0; i < tick_count; ++i)
	{
		//192 because we want only 3/4 of the gauge to have ticks, +96 for orientation
		degree = 192/(tick_count - 1) * i + 96;

		//do the initial calculation for offset vars
		tx = (radius * GetCos(degree)) / 512;
		ty = (radius * GetSin(degree)) / 512;

		//apply offsets to coordinates
		x1 = x + tx*3/4;
		y1 = y + ty*3/4;
		x2 = x + tx;
		y2 = y + ty;

		miniDisp->drawLine(x1, y1, x2, y2);
	}
	//draw face
	miniDisp->drawCircle(x, y, radius, U8G2_DRAW_ALL);

	//draw knob
	degree = map(val, min, max, 0, 192) + 96;
	x2 = x + (radius * GetCos(degree)) / 512;
	y2 = y + (radius * GetSin(degree)) / 512;
	miniDisp->drawLine(x, y, x2, y2);



}

//draw a bar gauge with corner at this coordinate
void drawBarGauge(INIT_CLASS *miniDisp, bool isHorizontal, short x, short y, short width, short height, int min, int max, int val)
{
	
	miniDisp->drawFrame(x, y, width, height);

	//how tall the "filled" box should be
	int fillHeight = map(val, min, max, 0, isHorizontal ? width : height);

	if(isHorizontal)
		miniDisp->drawBox(x, y, fillHeight, height);
	else
		miniDisp->drawBox(x, y + height - fillHeight, width, fillHeight);


}


//loop input between min and max value (like over/underflows) min<=x<max
int loopItem(int item, int min, int max)
{
    //make it so that min = 0
    item -= min;
    max -= min;

    if(item >= max)
        item = (item % max); //0+...
    else if(item < 0)
        item = max + (item % max) - 1;

    return item + min;//add min back


    //if(*selectedItem >= entryCount)
    //    *selectedItem = (*selectedItem % entryCount); //0+...
    //else if(*selectedItem < 0)
    //    *selectedItem = entryCount + (*selectedItem % entryCount);

}

//draw menu
bool putMenu(INIT_CLASS *miniDisp, int* selectedItem, const char** menuList, int entryCount)
{

    if (entryCount == 0)
        return false;


    //loop around selection
    *selectedItem = loopItem(*selectedItem, 0, entryCount);


    static int lastSelectedItem = 0;
    int fontHeight = 20;

    miniDisp->setFont(u8g2_font_helvB12_tr);//(u8g2_font_cu12_mr );
    //miniDisp->setFontMode(0); //non-transparent
    
    //we changed menu spots, we need to redraw
    if(lastSelectedItem != *selectedItem)
    {
        BeepBuzzer(20);//tick when we changed items
        lastSelectedItem = *selectedItem;

        //for each item that will fit on the screen
        int menuIndex;
        miniDisp->firstPage();
        do
        {
            for (int i = 0; i < DISPLAY_HEIGHT / fontHeight; ++i)
            {       
                //top entry is drawn different
                if(!i)
                {
                    //outline first entry in a selection box
                    miniDisp->drawBox(0, 0, DISPLAY_WIDTH, fontHeight);
                    menuIndex = *selectedItem; //don't need to loop for first entry
                    miniDisp->setDrawColor(0);//lit BG
                }
                else
                {
                    menuIndex = loopItem(*selectedItem + i, 0, entryCount);
                    miniDisp->setDrawColor(1);//dark BG
                }
                    
                miniDisp->drawStr(0,(i + 1) * fontHeight, menuList[menuIndex]);
            }
        } while (miniDisp->nextPage());

    }

    //TODO: de-bake this pin assignment
    return digitalRead(ENCODER_BUTTON);

}






