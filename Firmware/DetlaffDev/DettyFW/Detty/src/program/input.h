
#pragma once

#include <Arduino.h>
#include <Bounce2.h>


//unused abstraction layer class: if, for some reason, we can't use the bounce2 library,
//this would make it possible to link any backend into the code, but bounce2 should do everything we need
/*
class pushButton
{

    public:
        pushButton(int pin, int debounceTime, bool isNC);

        //update backend componets
        void update();

        //return if the button is CLICKED or not
        bool getCurrentState(void);

        //return if the button is RISING
        bool rose();
        bool fell();



    private:
        Bounce2::Button buttonObj = Bounce2::Button();





};
*/


class inputHandler
{

    public:
        //read and map pins based on their layout in the config file (constructor)
        inputHandler();
        ~inputHandler();



        //check the state of all input pins
        void update();


        Bounce2::Button triggerSwitch = Bounce2::Button();
        Bounce2::Button magReleaseSwitch = Bounce2::Button();

#ifdef USE_REV_TRIG
        Bounce2::Button revTriggerSwitch = Bounce2::Button();
#endif
        Bounce2::Button presetA = Bounce2::Button();
        Bounce2::Button presetB = Bounce2::Button();
        Bounce2::Button presetC = Bounce2::Button();
        Bounce2::Button encoderA = Bounce2::Button();
        Bounce2::Button encoderB = Bounce2::Button();
        Bounce2::Button encoderSwitch = Bounce2::Button();


    private:
        bool hasBeenInitialzed = false; //prevent more than one initialization



};




