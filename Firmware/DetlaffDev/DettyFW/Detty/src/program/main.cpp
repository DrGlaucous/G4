#include <Arduino.h>

#include "main.h"
#include "configuration.h"
#include "settings.h"
#include "input.h"
#include "utilities.h"
#include "flywheels.h"
#include "pusher.h"
#include "display.h"
#include "connectome.h"

all_settings_t gSettings;
inputHandler gPins;
flywheelHandler gFlywheel;
pusherHandler gPusher;
serialHandler gInfo(DEBUG_BAUD_RATE);
buzzerHandler gBuzzer(BUZZER);
menuHandler gMenu;
trigHandler gTrig; //trigonometry
connectomeHandler gConnectome;
//chronyHandler gChronograph;

//timer inturrupts to handle input buttons (actually just the encoder)
hw_timer_t *timer = NULL;
void IRAM_ATTR handleLoop()
{
    gPins.update_encoder();
    gBuzzer.update();
}


void setup() {
    // put your setup code here, to run once:

    //delay(1000);

    gMenu.start();


    //create inturrupt for encoder
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &handleLoop, true);
    timerAlarmWrite(timer, 1000, true); // every 0.01 seconds
    timerAlarmEnable(timer);

    //gInfo.send_message("weee");
    //gBuzzer.beep_multiple(10000, 30000, 10);

	//test
	//gChronograph.begin_isr();

}

void loop() {
    // put your main code here, to run repeatedly:

    gPins.update();
    gMenu.update();

    gConnectome.update();

	gFlywheel.update();
	gPusher.update();



	//test
	//I came head-first with this error. The fix was a single line, as mentioned in the link.
	//note https://github.com/espressif/esp-idf/issues/11867
	//we're getting occasional buffer overruns from bidirectional RMT.
	//see this: https://discord.com/channels/727038380054937610/1050619108007350343/1168263597172981810

	// unsigned long spd;
	// unsigned int cnt;

	// static unsigned long bggst_spd = 99999999;

	// gChronograph.get_darts(&spd, &cnt);

	// if(spd == 0)
	// 	spd = 1;
	
	// if(spd != 1 && spd < bggst_spd)
	// 	bggst_spd = spd;


	// float speed_fps = DART_LENGTH / (float)(spd) / 25.4 / 12 * 1E+6;               // feet per second
    // float speed_mps = DART_LENGTH / (float)(spd) / 1000 * 1E+6;                    // meter per second
    // float speed_mph = DART_LENGTH / (float)(spd) / 25.4 / 12 * 1E+6 / 5280 * 3600; // miles per hour  

	// Serial.printf("DC: %d || SPD: %.2f || SPD_MAX %d\n", cnt, speed_fps, bggst_spd);
}

