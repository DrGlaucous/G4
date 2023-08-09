
#include <Arduino.h>
#include <ESP32Servo.h>

#include "configuration.h"

#include "flywheels.h"



void singleMotor::attach(int pinNum,
                        unsigned int delayMillis,
                        flywheel_type_t flywheelType,
                        dshot_mode_t dshotMode = DSHOT_OFF,
                        bidirectional_mode_t dshotBidir = NO_BIDIRECTION)
{
    //prevent running this more than 1x
    if(has_been_attached)
        return;
    has_been_attached = true;

    //save settings to the class
    pin_num = pinNum;
    delay_millis = delayMillis;
    flywheel_type = flywheelType;
    dshot_mode = dshotMode;
    dshot_bidir = dshotBidir;

    //set up the output pin
    switch(flywheel_type)
    {
        default:
        case FLYWHEEL_TYPE_NULL:
            //nothing to initialize
            break;
        case FLYWHEEL_TYPE_BRUSHED:
            //set pin to analog out
            pinMode(pin_num, OUTPUT);
            break;
        case FLYWHEEL_TYPE_PWM:
            pwm_driver = new Servo();
            break;
        case FLYWHEEL_TYPE_DSHOT:
            dshot_driver = new DShotRMT(pin_num);
            break;


    }


}




//constuctor, assigns pins and creates ESC objects based on the contents of 'configuration.h'
flywheelHandler::flywheelHandler()
{

    //setup the flywheel type based on the defines we made earlier
    flywheel_type_t fType = FLYWHEEL_TYPE_NULL;
    dshot_mode_t dType = DSHOT_OFF;
    bidirectional_mode_t bType = NO_BIDIRECTION;
    unsigned int delayM = ESC_REV_DELAY;
    switch (ESC_TYPE)
    {
        case ESC_TYPE_BRUSHED:
            fType = FLYWHEEL_TYPE_BRUSHED;
            break;
        case ESC_TYPE_PWM:
            fType = FLYWHEEL_TYPE_PWM;

            break;
        case ESC_TYPE_DSHOT:
            fType = FLYWHEEL_TYPE_DSHOT;
            dType = ESC_DSHOT_MODE;
            bType = ENABLE_BIDIRECTION;
            break;
        default:
            fType = FLYWHEEL_TYPE_NULL;
            break;
    }


    //attach ESCs to their corresponding pins
    flywheelArray[0].attach(ESC_1, delayM, fType, dType, bType);
    flywheelArray[1].attach(ESC_2, delayM, fType, dType, bType);
#ifdef FOUR_ESCS 
    flywheelArray[2].attach(ESC_3, delayM, fType, dType, bType);
    flywheelArray[3].attach(ESC_4, delayM, fType, dType, bType);
#endif

}


void flywheelHandler::update()
{

    for(int i = 0; i < flywheel_count; ++i)
    {
        flywheelArray[i].update();
    }

}


