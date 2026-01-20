#include "app.h"
#include "app_state.h"
#include "ui.h"
#include "esp_log.h"
#include <string.h>

static const char *TAG = "app";

// Single source of truth
static app_state_t s_state;

void app_init(void)
{
    ESP_LOGI(TAG, "app_init(): initializing state and UI");
    
    // Initialize state with defaults
    app_state_init(&s_state);
    
    // Initialize UI and display home screen
    ui_init();
    
    // Bind initial state to UI
    ui_bind_home(&s_state);
}

app_state_t* app_get_state(void)
{
    return &s_state;
}

void app_update_time(const char *hour, const char *min)
{
    if (hour) {
        strncpy(s_state.hour_str, hour, sizeof(s_state.hour_str) - 1);
    }
    if (min) {
        strncpy(s_state.min_str, min, sizeof(s_state.min_str) - 1);
    }
    ui_bind_home(&s_state);
}

void app_update_stats(uint32_t steps, float kcal, float km)
{
    s_state.steps = steps;
    s_state.kcal = kcal;
    s_state.km = km;
    ui_bind_home(&s_state);
}
