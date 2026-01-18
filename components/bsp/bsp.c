#include "bsp.h"
#include "esp_log.h"
#include "lvgl.h"

// kommt aus display_spi.c
void bsp_display_init_and_register_lvgl(void);

static const char *TAG = "bsp";

void bsp_init(void)
{
    ESP_LOGI(TAG, "bsp_init(): init display + lvgl driver");
    bsp_display_init_and_register_lvgl();
}
