#include "board_config.h"

#include <assert.h>
#include "esp_log.h"
#include "esp_check.h"
#include "esp_heap_caps.h"

#include "driver/gpio.h"
#include "driver/spi_master.h"

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"

#include "lvgl.h"

static const char *TAG = "disp_spi";

static esp_lcd_panel_handle_t s_panel = NULL;
static esp_lcd_panel_io_handle_t s_io = NULL;

static lv_draw_buf_t s_draw_buf1;
static lv_draw_buf_t s_draw_buf2;
static lv_color_t *s_buf1 = NULL;
static lv_color_t *s_buf2 = NULL;
static lv_display_t *s_display = NULL;

// LVGL v9 flush callback signature
static void lv_flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    (void)disp;

    // LVGL area is inclusive; esp_lcd expects end exclusive
    const int x1 = area->x1;
    const int y1 = area->y1;
    const int x2 = area->x2 + 1;
    const int y2 = area->y2 + 1;

    esp_lcd_panel_draw_bitmap(s_panel, x1, y1, x2, y2, (const void *)px_map);

    // tell LVGL we are done flushing
    lv_display_flush_ready(disp);
}

static void backlight_init_on(void)
{
    if (PIN_LCD_BL < 0) return;

    gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL << PIN_LCD_BL,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    ESP_ERROR_CHECK(gpio_config(&io_conf));
    ESP_ERROR_CHECK(gpio_set_level(PIN_LCD_BL, 1));
}

static esp_err_t panel_init_spi(void)
{
    // 1) SPI bus
    spi_bus_config_t buscfg = {
        .sclk_io_num = PIN_SPI_SCLK,
        .mosi_io_num = PIN_SPI_MOSI,
        .miso_io_num = PIN_SPI_MISO,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = DISP_HOR_RES * 40 * sizeof(lv_color_t), // chunk
    };
    ESP_RETURN_ON_ERROR(spi_bus_initialize(SPI_HOST_ID, &buscfg, SPI_DMA_CH_AUTO), TAG, "spi_bus_initialize failed");

    // 2) Panel IO (SPI)
    esp_lcd_panel_io_spi_config_t iocfg = {
        .dc_gpio_num = PIN_LCD_DC,
        .cs_gpio_num = PIN_SPI_CS,
        .pclk_hz = SPI_CLK_HZ,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .spi_mode = 0,
        .trans_queue_depth = 10,
        .on_color_trans_done = NULL,
        .user_ctx = NULL,
    };
    ESP_RETURN_ON_ERROR(
        esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPI_HOST_ID, &iocfg, &s_io),
        TAG, "new_panel_io_spi failed"
    );

    // 3) Panel driver (API varies a bit by IDF version; keep it minimal)
    esp_lcd_panel_dev_config_t panel_cfg = {
        .reset_gpio_num = PIN_LCD_RST,
        .bits_per_pixel = 16,
    };

#if DISP_CTRL_ST7789
    ESP_RETURN_ON_ERROR(esp_lcd_new_panel_st7789(s_io, &panel_cfg, &s_panel), TAG, "new_panel_st7789 failed");
#elif DISP_CTRL_ILI9341
    ESP_RETURN_ON_ERROR(esp_lcd_new_panel_ili9341(s_io, &panel_cfg, &s_panel), TAG, "new_panel_ili9341 failed");
#elif DISP_CTRL_GC9A01
    ESP_RETURN_ON_ERROR(esp_lcd_new_panel_gc9a01(s_io, &panel_cfg, &s_panel), TAG, "new_panel_gc9a01 failed");
#else
#error "Select exactly one DISP_CTRL_* in board_config.h"
#endif

    ESP_RETURN_ON_ERROR(esp_lcd_panel_reset(s_panel), TAG, "panel_reset failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_init(s_panel), TAG, "panel_init failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_disp_on_off(s_panel, true), TAG, "disp_on_off failed");

    // 240x280 ST7789 panels: Set gap for correct pixel alignment
    // Gap (x, y) = (0, 20) - vertical offset to center visible area
    // This ensures pixel-perfect rendering without clipping
    esp_lcd_panel_set_gap(s_panel, 0, 20);
    
    // Invert colors for correct display on ST7789
    // Without this, colors appear as complementary (inverted)
    esp_lcd_panel_invert_color(s_panel, true);

    // Rotation (common mapping; you may tweak after first image)
#if (DISP_ROTATION_DEG == 0)
    esp_lcd_panel_swap_xy(s_panel, false);
    esp_lcd_panel_mirror(s_panel, false, false);
#elif (DISP_ROTATION_DEG == 90)
    esp_lcd_panel_swap_xy(s_panel, true);
    esp_lcd_panel_mirror(s_panel, true, false);
#elif (DISP_ROTATION_DEG == 180)
    esp_lcd_panel_swap_xy(s_panel, false);
    esp_lcd_panel_mirror(s_panel, true, true);
#elif (DISP_ROTATION_DEG == 270)
    esp_lcd_panel_swap_xy(s_panel, true);
    esp_lcd_panel_mirror(s_panel, false, true);
#else
#error "DISP_ROTATION_DEG must be 0/90/180/270"
#endif

    return ESP_OK;
}

void bsp_display_init_and_register_lvgl(void)
{
    ESP_LOGI(TAG, "init display + register LVGL driver");

    backlight_init_on();
    ESP_ERROR_CHECK(panel_init_spi());

    // --- LVGL v9 draw buffers ---
    const uint32_t buf_h = 40;
    const size_t buf_pixels = (size_t)DISP_HOR_RES * buf_h;
    const size_t buf_bytes  = buf_pixels * sizeof(lv_color_t);

    s_buf1 = heap_caps_malloc(buf_bytes, MALLOC_CAP_DMA);
    s_buf2 = heap_caps_malloc(buf_bytes, MALLOC_CAP_DMA);
    assert(s_buf1 && s_buf2);

    // Wrap raw buffers into LVGL draw buffer objects
    // RGB565_SWAPPED: Byte-swap for Big-Endian displays (ST7789)
    // Converts [0xef, 0x7b] -> [0x7b, 0xef] for correct color rendering
    lv_draw_buf_init(&s_draw_buf1, DISP_HOR_RES, buf_h, LV_COLOR_FORMAT_RGB565_SWAPPED, 0, s_buf1, buf_bytes);
    lv_draw_buf_init(&s_draw_buf2, DISP_HOR_RES, buf_h, LV_COLOR_FORMAT_RGB565_SWAPPED, 0, s_buf2, buf_bytes);

    // Create display and set flush callback
    // NO SCALING - native resolution for pixel-perfect rendering
    s_display = lv_display_create(DISP_HOR_RES, DISP_VER_RES);
    lv_display_set_flush_cb(s_display, lv_flush_cb);
    
    // Set color format to RGB565 with byte-swap for ST7789 (Big-Endian)
    // This fixes the color byte order: ESP32 (Little-Endian) -> ST7789 (Big-Endian)
    lv_display_set_color_format(s_display, LV_COLOR_FORMAT_RGB565_SWAPPED);

    // Provide the two draw buffers (no extra args in your LVGL)
    lv_display_set_draw_buffers(s_display, &s_draw_buf1, &s_draw_buf2);

    // Render mode: in this LVGL variant it's usually configured by the buffers themselves;
    // partial rendering is implied by smaller buffer height.
    // Buffer height 40 = ~30 FPS with stable rendering

    ESP_LOGI(TAG, "LVGL display registered (%dx%d, RGB565, no scaling)", DISP_HOR_RES, DISP_VER_RES);
}
