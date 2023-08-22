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

void setup() {
    // put your setup code here, to run once:

    gInfo.send_message("weee");
    gBuzzer.beep_multiple(10, 30, 10);
    //setup2();
    gMenu.start();
}

void loop() {
    // put your main code here, to run repeatedly:
	//loop2();
    gMenu.update();

    gPins.update();
    //gMenu.update();

    gBuzzer.update();
	gFlywheel.update();
	gPusher.update();


}

