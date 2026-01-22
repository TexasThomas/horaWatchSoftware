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

void app_update_today(const char *total)
{
    if (total) {
        strncpy(s_state.today_total, total, sizeof(s_state.today_total) - 1);
    }
    ui_bind_home(&s_state);
}

void app_set_activity(const char *name)
{
    if (name) {
        strncpy(s_state.activity_name, name, sizeof(s_state.activity_name) - 1);
    }
    ui_bind_home(&s_state);
}