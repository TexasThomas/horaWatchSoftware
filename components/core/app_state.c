#include "app_state.h"
#include <string.h>

void app_state_init(app_state_t *state)
{
    // Date/Time
    strcpy(state->date_str, "04-06");
    strcpy(state->hour_str, "09");
    strcpy(state->min_str, "40");
    
    // Fitness stats (demo values like in image)
    state->steps = 10349;
    state->kcal = 103.4f;
    state->km = 103.4f;
    
    // Device status
    state->battery_pct = 100;
    state->is_connected = false;
}