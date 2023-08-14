#pragma once



#include <Arduino.h>
#include "configuration.h"


//a wrapper for serial communication
class serialHandler
{
    public:
        serialHandler(int baudRate);
        ~serialHandler();
        void send_message(const char* message);
        void send_message_line(const char* message);



};




//buzzer handler: let's make some noize!
//currently only supports active buzzers (beep when a signal is applied)
class buzzerHandler
{
    public:
        buzzerHandler(int pinNo);
        void update();
        void beep_single(unsigned int millisOn);
        void set_beep(bool on);
        void beep_multiple(unsigned int millisOn, unsigned int millisOff, unsigned int countTimes);
        void beep_multiple_continuous(unsigned int millisOn, unsigned int millisOff);
    
    private:

        int pin_no = 0;

        unsigned long start_millis = 0;
        //millis() - start_millis
        unsigned long current_millis = 0;
        //used to detect a change in ticks
        unsigned long last_millis = 0;

        unsigned int millis_on = 0;
        unsigned int millis_off = 0;
        unsigned int count_times = 0;
        bool loop = false;

        inline void set_pin(int pinNo, bool value);

};




