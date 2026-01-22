#include "app_state.h"
#include <string.h>

void app_state_init(app_state_t *state)
{
    // Timer display
    strcpy(state->timer_hhmm, "00:00");
    strcpy(state->timer_ss, "00");
    
    // Today total (as shown in image)
    strcpy(state->today_total, "2:13:10");
    
    // Activity
    strcpy(state->activity_name, "Reading");
    
    // State
    state->is_running = false;
    state->battery_pct = 100;
}