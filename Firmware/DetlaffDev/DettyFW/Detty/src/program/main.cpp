#include <Arduino.h>

#include "main.h"
#include "configuration.h"
#include "input.h"
#include "utilities.h"
#include "flywheels.h"
#include "pusher.h"
//#include "display.h"
#include "DispTest.h"

inputHandler gPins;
flywheelHandler gFlywheel;
pusherHandler gPusher;
serialHandler gInfo(DEBUG_BAUD_RATE);
buzzerHandler gBuzzer(BUZZER);
menuHandler gMenu;

//timer inturrupts to handle input buttons
hw_timer_t *timer = NULL;
void IRAM_ATTR handleLoop()
{
    gPins.update();
}


void setup() {
    // put your setup code here, to run once:

    gInfo.send_message("weee");
    gBuzzer.beep_multiple(10, 30, 10);
    //setup2();
    gMenu.start();

    //create inturrupt
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &handleLoop, true);
    timerAlarmWrite(timer, 1000, true); // every 0.01 seconds
    timerAlarmEnable(timer);
}

void loop() {
    // put your main code here, to run repeatedly:
	//loop2();
    gMenu.update();

    //gPins.update();
    //gMenu.update();

    gBuzzer.update();
	gFlywheel.update();
	gPusher.update();


}

