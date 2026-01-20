#include "ui.h"

/*===========================================================================
 * Color Tokens - Smartwatch Dark Theme (like reference image)
 *===========================================================================*/

// Background
#define COLOR_BG_BLACK      lv_color_hex(0x000000)   // Pure black (OLED)
#define COLOR_BG_PANEL      lv_color_hex(0x1C1C1E)   // Dark panel background

// Time - Vibrant green (like reference)
#define COLOR_TIME_GREEN    lv_color_hex(0x32CD32)   // Lime green for big time

// Text
#define COLOR_TEXT_WHITE    lv_color_hex(0xFFFFFF)   // Pure white
#define COLOR_TEXT_GRAY     lv_color_hex(0x8E8E93)   // iOS gray

// Accent
#define COLOR_BATTERY_CYAN  lv_color_hex(0x00D4FF)   // Cyan for battery

/*===========================================================================
 * Static Style Objects
 *===========================================================================*/
static lv_style_t style_bg;
static lv_style_t style_time_big;
static lv_style_t style_date;
static lv_style_t style_stat_panel;
static lv_style_t style_stat_value;
static lv_style_t style_stat_unit;
static lv_style_t style_battery;

/*===========================================================================
 * Style Initialization
 *===========================================================================*/

void ui_styles_init(void)
{
    // ===== Background - Pure black =====
    lv_style_init(&style_bg);
    lv_style_set_bg_color(&style_bg, COLOR_BG_BLACK);
    lv_style_set_bg_opa(&style_bg, LV_OPA_COVER);
    lv_style_set_border_width(&style_bg, 0);
    lv_style_set_pad_all(&style_bg, 0);
    lv_style_set_radius(&style_bg, 0);
    
    // ===== Big Time Digits - Huge green numbers =====
    lv_style_init(&style_time_big);
    lv_style_set_text_color(&style_time_big, COLOR_TIME_GREEN);
    lv_style_set_text_font(&style_time_big, &lv_font_montserrat_48);  // Will use largest available
    lv_style_set_text_align(&style_time_big, LV_TEXT_ALIGN_LEFT);
    
    // ===== Date - Small white text at top =====
    lv_style_init(&style_date);
    lv_style_set_text_color(&style_date, COLOR_TEXT_WHITE);
    lv_style_set_text_font(&style_date, &lv_font_montserrat_14);
    lv_style_set_text_align(&style_date, LV_TEXT_ALIGN_CENTER);
    
    // ===== Stat Panel - Dark rounded container =====
    lv_style_init(&style_stat_panel);
    lv_style_set_bg_color(&style_stat_panel, COLOR_BG_PANEL);
    lv_style_set_bg_opa(&style_stat_panel, LV_OPA_COVER);
    lv_style_set_radius(&style_stat_panel, 12);
    lv_style_set_pad_all(&style_stat_panel, 8);
    lv_style_set_border_width(&style_stat_panel, 0);
    
    // ===== Stat Value - White numbers =====
    lv_style_init(&style_stat_value);
    lv_style_set_text_color(&style_stat_value, COLOR_TEXT_WHITE);
    lv_style_set_text_font(&style_stat_value, &lv_font_montserrat_14);
    lv_style_set_text_align(&style_stat_value, LV_TEXT_ALIGN_CENTER);
    
    // ===== Stat Unit - Gray labels =====
    lv_style_init(&style_stat_unit);
    lv_style_set_text_color(&style_stat_unit, COLOR_TEXT_GRAY);
    lv_style_set_text_font(&style_stat_unit, &lv_font_montserrat_12);
    lv_style_set_text_align(&style_stat_unit, LV_TEXT_ALIGN_CENTER);
    
    // ===== Battery - Cyan text =====
    lv_style_init(&style_battery);
    lv_style_set_text_color(&style_battery, COLOR_BATTERY_CYAN);
    lv_style_set_text_font(&style_battery, &lv_font_montserrat_14);
    lv_style_set_text_align(&style_battery, LV_TEXT_ALIGN_LEFT);
}

/*===========================================================================
 * Style Getters
 *===========================================================================*/

lv_style_t* ui_style_bg(void)           { return &style_bg; }
lv_style_t* ui_style_time_big(void)     { return &style_time_big; }
lv_style_t* ui_style_date(void)         { return &style_date; }
lv_style_t* ui_style_stat_panel(void)   { return &style_stat_panel; }
lv_style_t* ui_style_stat_value(void)   { return &style_stat_value; }
lv_style_t* ui_style_stat_unit(void)    { return &style_stat_unit; }
lv_style_t* ui_style_battery(void)      { return &style_battery; }
