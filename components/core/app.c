#include "app.h"
#include "app_state.h"
#include "ui.h"
#include "esp_log.h"
#include <string.h>

static const char *TAG = "app";

static app_state_t s_state;

void app_init(void)
{
    ESP_LOGI(TAG, "app_init(): initializing state and UI");
    
    app_state_init(&s_state);
    ui_init();
    ui_bind_home(&s_state);
}

app_state_t* app_get_state(void)
{
    return &s_state;
}

void app_toggle_picker(void)
{
    s_state.picker_open = !s_state.picker_open;
    ESP_LOGI(TAG, "Picker %s", s_state.picker_open ? "opened" : "closed");
    ui_bind_home(&s_state);
}

void app_set_category(category_t cat)
{
    if (cat < CATEGORY_COUNT) {
        s_state.current_category = cat;
        s_state.picker_open = false;  // Close picker after selection
        ESP_LOGI(TAG, "Category changed to: %s", app_get_category_name(cat));
        ui_bind_home(&s_state);
    }
}

void app_update_timer(const char *hhmm, const char *ss)
{
    if (hhmm) {
        strncpy(s_state.timer_hhmm, hhmm, sizeof(s_state.timer_hhmm) - 1);
    }
    if (ss) {
        strncpy(s_state.timer_ss, ss, sizeof(s_state.timer_ss) - 1);
    }
    ui_bind_home(&s_state);
}