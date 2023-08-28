#include <Arduino.h>

#include "main.h"
#include "configuration.h"
#include "input.h"
#include "utilities.h"
#include "flywheels.h"
#include "pusher.h"
#include "display.h"
#include "DispTest.h"

inputHandler gPins;
flywheelHandler gFlywheel;
pusherHandler gPusher;
serialHandler gInfo(DEBUG_BAUD_RATE);
buzzerHandler gBuzzer(BUZZER);
menuHandler gMenu;
trigHandler gTrig; //trigonometry

//timer inturrupts to handle input buttons (actually just the encoder)
hw_timer_t *timer = NULL;
void IRAM_ATTR handleLoop()
{
    gPins.update_encoder();
    gBuzzer.update();
}


void setup() {
    // put your setup code here, to run once:
    gMenu.start();

    //create inturrupt
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &handleLoop, true);
    timerAlarmWrite(timer, 1000, true); // every 0.01 seconds
    timerAlarmEnable(timer);

    gInfo.send_message("weee");
    gBuzzer.beep_multiple(10000, 30000, 10);

}

void loop() {
    // put your main code here, to run repeatedly:
	//loop2();
    gPins.update();
    gMenu.update();

	gFlywheel.update();
	gPusher.update();


}

