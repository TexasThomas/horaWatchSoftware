#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "lvgl.h"
#include "bsp.h"
#include "app.h"

static const char *TAG = "main";

void app_main(void)
{
    ESP_LOGI(TAG, "Booting horaWatchSoftware...");

    bsp_init();   // Step 4 wird hier Display driver registrieren
    lv_init();    // LVGL core init

    app_init();   // creates "Hello LVGL" label

    while (1) {
        lv_timer_handler();
        app_tick();
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}
