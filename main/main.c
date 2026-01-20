#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include <esp_timer.h>
#include "esp_task_wdt.h"

#include "lvgl.h"
#include "bsp.h"
#include "app.h"

static const char *TAG = "main";

static SemaphoreHandle_t s_lvgl_mutex;

static void lvgl_tick_cb(void *arg)
{
    (void)arg;
    lv_tick_inc(1); // 1 ms tick
}

static void lvgl_task(void *arg)
{
    (void)arg;

    // Add this task to the watchdog
    esp_task_wdt_add(NULL);

    while (1) {
        // LVGL is not thread-safe -> guard
        if (xSemaphoreTake(s_lvgl_mutex, portMAX_DELAY) == pdTRUE) {
            lv_timer_handler();
            xSemaphoreGive(s_lvgl_mutex);
        }

        // Feed the watchdog to prevent timeout
        esp_task_wdt_reset();

        // Yield so IDLE task can run (prevents WDT)
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "Booting horaWatchSoftware...");

    lv_init();    // 1) LVGL core init
    bsp_init();   // 2) init panel + register LVGL display driver

    // Mutex for LVGL
    s_lvgl_mutex = xSemaphoreCreateMutex();
    configASSERT(s_lvgl_mutex);

    // 1ms tick timer
    const esp_timer_create_args_t tick_args = {
        .callback = &lvgl_tick_cb,
        .arg = NULL,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "lv_tick"
    };
    esp_timer_handle_t tick_timer;
    ESP_ERROR_CHECK(esp_timer_create(&tick_args, &tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(tick_timer, 1000)); // 1000 us = 1 ms

    // Create UI (must be inside LVGL lock)
    xSemaphoreTake(s_lvgl_mutex, portMAX_DELAY);
    app_init(); // creates "Hello LVGL"
    xSemaphoreGive(s_lvgl_mutex);

    // LVGL task pinned to core 1 (keeps main free)
    xTaskCreatePinnedToCore(lvgl_task, "lvgl", 8192, NULL, 5, NULL, 1);
    
    // Keep app_main alive - required for LVGL demo timers
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
