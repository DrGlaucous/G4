#pragma once

#include <DShotRMT.h>
#include <Arduino.h>

#include <ESP32Servo.h>
#include <DShotRMT.h>

#include "configuration.h"


typedef enum flywheel_type_e
{
    FLYWHEEL_TYPE_NULL,
    FLYWHEEL_TYPE_BRUSHED,
    FLYWHEEL_TYPE_PWM,
    FLYWHEEL_TYPE_DSHOT,
}flywheel_type_t;

class singleMotor
{

    public:
    //relate a pin and flywheel type
    void attach(int pinNum,
                unsigned int delayMillis,
                flywheel_type_t flywheelType,
                dshot_mode_t dshotMode = DSHOT_OFF,
                bidirectional_mode_t dshotBidir = NO_BIDIRECTION);

    //returns TRUE if flywheel has reached speed
    bool update();

    //set and get the target speed of the flywheel, 
    void set_target_speed(int speed);
    int get_target_speed();

    //ONLY works with bidirectional dshot.
    //Otherwise, it returns 0 if the delay hasn't run out yet, returns target_speed if it has
    //if set to true, it returns the real RPM number of the motors,
    //otherwise, it returns mapped value from 0 to the target speed. This will be incorrect unless calibrate_speed() is called
    void get_current_speed(bool actualSpeed);

    //runs the motor at the max DSHOT speed and reads the RPM value, using that to map RPM back to DSHOT speed
    //returns TRUE when finished
    bool calibrate_speed();


    private:

    //motor settings

    //if we assign a pin number of -1, we essentialy enable a dummy motor

    int current_speed = 0; //speed the motor is trying to reach
    int last_speed = 0; //speed the motor is reaching from
    bool reached_speed = false; //did the motor reach its target?
    unsigned int delay_millis = 0; //how long until the motor is revved at speed
    unsigned long current_millis = 0; //how much delay is left
    unsigned long start_millis = 0; //when the command to change speed was issued



    bool is_valid_motor = false; //pin number needs to be valid
    bool has_been_attached = false; //prevent attach() from happening more than 1x
    int pin_num = -1; //pin to attach to, invalid by default

    flywheel_type_t flywheel_type = FLYWHEEL_TYPE_NULL;
    dshot_mode_t dshot_mode = DSHOT_OFF;
    bidirectional_mode_t dshot_bidir = NO_BIDIRECTION;


    //motor driver containers, objects are allocated as needed, depending on the mode
    DShotRMT* dshot_driver = NULL;
    Servo* pwm_driver = NULL;
    


};

//handles all flywheels
class flywheelHandler
{
    public:
    flywheelHandler();
    ~flywheelHandler();
    void update();

    bool at_speed;


    private:

    //milliseconds of delay before ESCs are considered "At Speed"
    //this value is not used with bidirectional dshot
    unsigned int delay_millis = 0;


    //this array holds the individual flywheel objects
#ifdef FOUR_ESCS
    int flywheel_count = 4;
    singleMotor flywheelArray[4];
#else
    int flywheel_count = 2;
    singleMotor flywheelArray[2];
#endif



};