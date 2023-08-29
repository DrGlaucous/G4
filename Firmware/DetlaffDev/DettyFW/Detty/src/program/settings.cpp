

#include <Arduino.h>
#include "configuration.h"


typedef enum shoot_mode_e
{
    SHOOT_MODE_NULL,
    SHOOT_MODE_FULL_AUTO,
    SHOOT_MODE_SELECT_FIRE,
    SHOOT_MODE_MAX,
}shoot_mode_t;

//all settings in the blaster (as set by configuration.h)
typedef struct all_settings_s
{

    unsigned int esc_rev_delay;

    unsigned int min_flywheel_speed;
    unsigned int max_flywheel_speed;

    unsigned int esc_output_min;
    unsigned int esc_output_max;

    unsigned int esc_rpm_min;
    unsigned int esc_rpm_max;

    live_settings_t preset_settings[3];

} all_settings_t;

//the settings for a single configuration (selectable with the preset buttons)
typedef struct live_settings_s
{
    
    shoot_mode_t shoot_mode;

    unsigned int cache_delay;
    unsigned int 

} live_settings_t;



