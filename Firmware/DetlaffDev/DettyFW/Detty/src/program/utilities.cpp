#include <Arduino.h>
#include "configuration.h"

#include "utilities.h"



//serial wrapper functions:

serialHandler::serialHandler(int baudRate)
{
    Serial.begin(baudRate);
}
serialHandler::~serialHandler()
{
    Serial.end(true);
}
void serialHandler::send_message(const char* message)
{
    Serial.print(message);
}
void serialHandler::send_message_line(const char* message)
{
    Serial.println(message);
}


//buzzer functions:

buzzerHandler::buzzerHandler(int pinNo)
{
    pin_no = pinNo;
    //do not initialize an output if we set the pin to -1
    if(pinNo == -1)
        return;

    pinMode(pinNo, OUTPUT);
    digitalWrite(pinNo, LOW);
}
void buzzerHandler::update()
{

    //only check on the tick changeover
    if(millis() == last_millis)
        return;

    //ensure the buzzer is OFF when we run out of cycles
    if(count_times < 1 && loop == false)
    {
        set_pin(pin_no, LOW);
        return;
    }

    current_millis = millis() - start_millis;

    //after low time, decrement count and switch pin ON
    if(current_millis > millis_on + millis_off)
    {
        start_millis = millis();
        --count_times;
    }
    else if(current_millis > millis_on)
    {
        set_pin(pin_no, LOW);
    }
    else
    {
        set_pin(pin_no, HIGH);
    }

    last_millis = millis();

}
void buzzerHandler::beep_single(unsigned int millisOn)
{
    millis_on = millisOn;
    millis_off = 0;
    count_times = 1;
    current_millis = millis();
    start_millis = current_millis;
    loop = false;
}
void buzzerHandler::beep_multiple(unsigned int millisOn, unsigned int millisOff, unsigned int countTimes)
{
    millis_on = millisOn;
    millis_off = millisOff;
    count_times = countTimes;
    current_millis = millis();
    start_millis = current_millis;
    loop = false;
}
void buzzerHandler::beep_multiple_continuous(unsigned int millisOn, unsigned int millisOff)
{
    millis_on = millisOn;
    millis_off = millisOff;
    current_millis = millis();
    start_millis = current_millis;
    loop = true;
}
void buzzerHandler::set_beep(bool on)
{
    set_pin(pin_no, on);
    loop = true;
}
//handle -1 pins
inline void buzzerHandler::set_pin(int pinNo, bool value)
{
    if(pinNo < 0)
        return;
    digitalWrite(pinNo, value);
}


//trig functions
trigHandler::trigHandler()
{
    for (int i = 0; i < 0x100; ++i)
            sinTbl[i] = (short)(sin(i * TWO_PI / 256.0) * 512.0);
}

short trigHandler::GetSin(unsigned char deg)
{
	return sinTbl[deg];
}

short trigHandler::GetCos(unsigned char deg)
{
	deg += 0x40;//90 degree offset
	return sinTbl[deg];
}


