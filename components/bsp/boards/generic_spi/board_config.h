#pragma once

// ========= Display basics =========
#define DISP_HOR_RES      240
#define DISP_VER_RES      280
#define DISP_ROTATION_DEG 0

// ========= SPI pins (ST7789) =========
#define PIN_SPI_MOSI  23
#define PIN_SPI_MISO  -1
#define PIN_SPI_SCLK  18
#define PIN_SPI_CS    5
#define PIN_LCD_DC    16
#define PIN_LCD_RST   17
#define PIN_LCD_BL    4

// ========= SPI config =========
#define SPI_HOST_ID   SPI2_HOST
#define SPI_CLK_HZ    (40 * 1000 * 1000)   // falls Probleme: 20*1000*1000

// ========= Display controller selection =========
#define DISP_CTRL_ST7789  1
#define DISP_CTRL_ILI9341 0
#define DISP_CTRL_GC9A01  0
