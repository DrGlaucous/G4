
#include <Arduino.h>

#include "main.h"
#include "configuration.h"
#include "connectome.h"



connectomeHandler::connectomeHandler()
{

}


void connectomeHandler::update()
{

    live_settings_t *currentSet = &gSettings.preset_settings[gSettings.selected_preset];

    switch(currentSet->shoot_mode)
    {
        default:
        case SHOOT_MODE_NULL:
            break;
        case SHOOT_MODE_FULL_AUTO:
            if(gPins.triggerSwitch.pressed())
            {
                gPusher.pushBurst(currentSet->pusher_rate, 3);
                //Serial.println("press");
            }
            if(gPins.triggerSwitch.released())
            {
                gPusher.halt();
                //Serial.println("release");
            }

            break;
        case SHOOT_MODE_SELECT_FIRE:
        case SHOOT_MODE_CACHE:
            break;
    }


}










