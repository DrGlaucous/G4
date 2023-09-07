
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

    //reset cache vars when the mode is switched out
    if(currentSet->shoot_mode != SHOOT_MODE_CACHE)
        cache_in_progress = false;

    switch(currentSet->shoot_mode)
    {
        default:
        case SHOOT_MODE_NULL:
            break;
        case SHOOT_MODE_FULL_AUTO:
            triggerTypeHandler();
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
            triggerTypeHandler();

            if(connectome_trigger)
            {
                if(connectome_trigger_changed) //start flywheels
                {
                    connectome_trigger_changed = false;
                    gFlywheel.set_target_speed(currentSet->flywheel_speed);
                    Serial.println("set speed");
                }
                else if(gFlywheel.at_speed && !gPusher.is_pushing && !push_in_progress) //once flywheels have revved, begin pushing only if we're not already doing so
                {
                    gPusher.pushBurst(currentSet->pusher_rate, currentSet->burst_count);
                    push_in_progress = true;
                    Serial.println("begin push");

                }
                else if(!gPusher.is_pushing && push_in_progress && !cycle_completed) //done pushing
                {
                    gFlywheel.set_target_speed(0);
                    connectome_trigger = false; //depress trigger (if in commit mode, the user will just re-press this next frame)
                    connectome_trigger_changed = true;
                    cycle_completed = true;
                    Serial.println("end push");
                }

                //if the user is still holding down the trigger in commit mode, nothing will happen

            }
            else if(connectome_trigger_changed) //nothing is pressed, reset states
            {
                Serial.println("released");
                gPusher.halt();
                gFlywheel.set_target_speed(0);
                push_in_progress = false; //only reset this if we let off the trigger
                connectome_trigger = false;
                connectome_trigger_changed = false;
                cycle_completed = false;
            }


            break;
        case SHOOT_MODE_CACHE:

            //start pushing once the cache is over
            if(cache_in_progress && millis() - press_start > currentSet->cache_delay)
            {
                if(gFlywheel.at_speed && !gPusher.is_pushing) //start pusher
                {
                    if(!push_in_progress) //use this to tell us if we started the pusher
                    {
                        gPusher.pushBurst(currentSet->pusher_rate, cache_burst_total);
                        push_in_progress = true; //have we sent the push command
                    }
                    else //we finished a cache cylce, reset
                    {
                        cache_in_progress = false;
                        push_in_progress = false;
                        Serial.println("finish");
                    }
                }

            }
            else if(gPins.triggerSwitch.pressed()) //start the push cycle
            {
                if(cache_in_progress)
                {
                    ++cache_burst_total;
                }
                else
                {
                    press_start = millis();
                    gFlywheel.set_target_speed(currentSet->flywheel_speed);
                    cache_burst_total = 1;
                    cache_in_progress = true;
                }
            }

            break;
    }


}


void connectomeHandler::triggerTypeHandler(bool release)
{
    live_settings_t *currentSet = &gSettings.preset_settings[gSettings.selected_preset];
    
    switch(currentSet->trigger_mode)
    {
        case TRIGGER_MODE_NULL:
            break;
        case TRIGGER_MODE_COMMIT:

            connectome_trigger = gPins.triggerSwitch.isPressed();
            connectome_trigger_changed = gPins.triggerSwitch.changed();

            break;
        case TRIGGER_MODE_PRESS:

            if(gPins.triggerSwitch.pressed())
            {
                connectome_trigger = true;
                connectome_trigger_changed = true;
            }

            break;


    }
}







