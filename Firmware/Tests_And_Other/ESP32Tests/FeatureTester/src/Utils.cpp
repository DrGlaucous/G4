#include <Arduino.h>

//setup encoder stuff here (must be before library)
#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

#include "Configuration.h"


unsigned long MillisecondTicks{};
unsigned long MicrosecondTicks{};
unsigned long LastMillisecondTicks{};
unsigned long LastMicrosecondTicks{};

void GetTicks(void)
{
	LastMillisecondTicks = MillisecondTicks;
	LastMicrosecondTicks = MicrosecondTicks;

	MillisecondTicks = millis();
	MicrosecondTicks = micros();
}


void InitPins(void)
{
#ifdef BUZZER
    pinMode(BUZZER, OUTPUT);
#endif
}


//handle user input



Encoder testEncode(ENCODER_A, ENCODER_B);

//returns +1 if the encoder changed up, -1 if it changed down, or 0 if no change
int GetUserInput()
{
	int encodeResult = testEncode.read();
	testEncode.write(0);
	return encodeResult;
}






int buzzerTimeout = 0;
//use this to make the buzzer beep for X milliseconds
void BeepBuzzer(int millis)
{
#ifdef BUZZER 
    buzzerTimeout = millis;
    digitalWrite(BUZZER, HIGH);
#endif
}

//processes the buzzer time left
void TickBuzzer()
{
#ifdef BUZZER 
    digitalWrite(BUZZER, LOW);

    //if(buzzerTimeout)
    //    if(MillisecondTicks != LastMillisecondTicks)
    //        --buzzerTimeout;
    //else
    //    digitalWrite(BUZZER, LOW);
#endif
}
























