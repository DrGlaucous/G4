#pragma once


#include <Arduino.h>

#include "main.h"
#include "configuration.h"


//there are 2 main types of firing operations: full auto and select fire
//there are multiple attributes that can be added to the select fire modes, such as:
//cache fire (firing window)
//commit fire (trigger must be held until flywheels are at speed)


typedef enum shoot_type_flag_e
{
    SEL_ATTR_CACHE = 1 << 0,
    SEL_ATTR_COMMIT = 1 << 1,
    
} shoot_type_flag_t;



class connectomeHandler
{
    public:

        connectomeHandler();
        void update();



    private:





};
