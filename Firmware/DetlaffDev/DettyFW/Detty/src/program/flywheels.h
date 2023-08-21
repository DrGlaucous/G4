#pragma once

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
                        bidirectional_mode_t dshotBidir = NO_BIDIRECTION,
                        int outMin = 0, int outMax = 100,
                        int rpmMin = 0, int rpmMax = 100
                        );

    //begin sending values out to the motor
    void start();

    //returns TRUE if flywheel has reached speed
    bool update();

    //set and get the target speed of the flywheel, 
    void set_target_speed(int speed);
    int get_target_speed();

    //ONLY works with bidirectional dshot.
    //Otherwise, it returns a mapped value based on its current delay
    //if set to true, it returns the real RPM number of the motors,
    //otherwise, it returns mapped value from 0 to the target speed. This will be incorrect unless calibrate_speed() is called
    int get_current_speed(bool actualSpeed);

    //runs the motor at the max DSHOT speed and reads the RPM value, using that to map RPM back to DSHOT speed
    //returns TRUE when finished
    //run this consecutively instead of update()
    bool calibrate_speed();


    private:

    //motor settings
    //if we assign a pin number of -1, we enable a dummy motor
    unsigned int delay_millis = 0; //how long until the motor is revved at max speed
    flywheel_type_t flywheel_type = FLYWHEEL_TYPE_NULL;
    dshot_mode_t dshot_mode = DSHOT_OFF;
    bidirectional_mode_t dshot_bidir = NO_BIDIRECTION;


    ////////dynamic variables////////

    int target_speed = 0; //speed the motor is trying to reach

    int last_speed = 0; //speed the motor is reaching from (old current_speed value)
    int current_speed = 0; //speed the motor is at now

    unsigned long last_millis = 0; //for changing only 1x per tick

    //with D_Shot, we need to manually send a packet every several milliseconds or so, but they can't be back-to-back.
    //this makes sure that there is some space between each transmission
    unsigned short counter_millis = 0;

    unsigned int transition_millis = 0; //how long the motor should take going from last_speed to target_speed
    unsigned int start_transition_millis = 0; //know where we started from for mapping transition_millis

    int pin_num = -1; //pin to attach to, invalid by default


    //bool is_valid_motor = false; //pin number needs to be valid
    bool has_been_attached = false; //prevent attach() from happening more than 1x


    //motor driver containers, objects are allocated as needed, depending on the mode
    DShotRMT* dshot_driver = NULL;
    Servo* pwm_driver = NULL;


    //see the description for these variables in 'configuration.h'
    int output_min = 0;
    int output_max = 100;
    //only used when we're actually writing the value to the motor

    //ditto about description
    int rpm_min = 0;
    int rpm_max = 100;
    //current_speed, last_speed, and target_speed bounce between these two values


};

//handles all flywheels
class flywheelHandler
{
    public:
    flywheelHandler();
    //~flywheelHandler();
    void update();

    //is the cage at speed?
    bool at_speed;

    //how fast should the cage go?
    //motor objects can process this value raw
    int target_speed;


    private:


    //this array holds the individual flywheel objects
#ifdef FOUR_ESCS
    int flywheel_count = 4;
    singleMotor flywheelArray[4];
#else
    int flywheel_count = 2;
    singleMotor flywheelArray[2];
#endif


};