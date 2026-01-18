#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "bsp.h"
#include "app.h"

static const char *TAG = "main";

void app_main(void)
{
    ESP_LOGI(TAG, "Booting horaWatchSoftware...");

    bsp_init();
    app_init();

    while (1) {
        ESP_LOGI(TAG, "loop...");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

