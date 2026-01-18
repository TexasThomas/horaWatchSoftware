#include "app.h"
#include "esp_log.h"
#include "ui.h"

static const char *TAG = "core";

static ui_t ui;

void app_init(void)
{
    ESP_LOGI(TAG, "app_init(): initializing UI");
    ui_init(&ui);
}

void app_tick(void)
{
    ui_tick(&ui);
}
