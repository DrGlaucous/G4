#include <Arduino.h>

#include "main.h"
#include "configuration.h"
#include "input.h"
#include "utilities.h"
#include "flywheels.h"
#include "pusher.h"

inputHandler gPins;
flywheelHandler gFlywheel;
pusherHandler gPusher;
serialHandler gInfo(DEBUG_BAUD_RATE);
buzzerHandler gBuzzer(BUZZER);

void setup() {
    // put your setup code here, to run once:

    gInfo.send_message("weee");
    gBuzzer.beep_multiple(10, 30, 10);

}

void loop() {
    // put your main code here, to run repeatedly:
	
    gPins.update();


    gBuzzer.update();
	gFlywheel.update();
	gPusher.update();


}

