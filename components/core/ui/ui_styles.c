#include "ui.h"

/*===========================================================================
 * Color Tokens - Exact colors from reference image
 *===========================================================================*/

// Background
#define COLOR_BG_BLACK      lv_color_hex(0x000000)   // Pure black

// Timer - Cyan/Turquoise (like in image)
#define COLOR_CYAN          lv_color_hex(0x00E5E5)   // Bright cyan

// Today/Activity - Yellow/Orange (like in image)
#define COLOR_YELLOW        lv_color_hex(0xE5A800)   // Golden yellow

// Button background
#define COLOR_BTN_BG        lv_color_hex(0x2A2A2A)   // Dark gray

/*===========================================================================
 * Static Style Objects
 *===========================================================================*/
static lv_style_t style_bg;
static lv_style_t style_timer_frame;
static lv_style_t style_timer_text;
static lv_style_t style_timer_seconds;
static lv_style_t style_today_text;
static lv_style_t style_activity_btn;
static lv_style_t style_activity_text;

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
    
    // ===== Timer Frame - Cyan border, rounded =====
    lv_style_init(&style_timer_frame);
    lv_style_set_bg_color(&style_timer_frame, COLOR_BG_BLACK);
    lv_style_set_bg_opa(&style_timer_frame, LV_OPA_COVER);
    lv_style_set_border_color(&style_timer_frame, COLOR_CYAN);
    lv_style_set_border_width(&style_timer_frame, 2);
    lv_style_set_border_opa(&style_timer_frame, LV_OPA_COVER);
    lv_style_set_radius(&style_timer_frame, 12);
    lv_style_set_pad_all(&style_timer_frame, 10);
    
    // ===== Timer Text - Big cyan digits =====
    lv_style_init(&style_timer_text);
    lv_style_set_text_color(&style_timer_text, COLOR_CYAN);
    lv_style_set_text_font(&style_timer_text, &lv_font_montserrat_48);
    lv_style_set_text_align(&style_timer_text, LV_TEXT_ALIGN_CENTER);
    
    // ===== Timer Seconds - Small cyan =====
    lv_style_init(&style_timer_seconds);
    lv_style_set_text_color(&style_timer_seconds, COLOR_CYAN);
    lv_style_set_text_font(&style_timer_seconds, &lv_font_montserrat_18);
    lv_style_set_text_align(&style_timer_seconds, LV_TEXT_ALIGN_LEFT);
    
    // ===== Today Text - Yellow =====
    lv_style_init(&style_today_text);
    lv_style_set_text_color(&style_today_text, COLOR_YELLOW);
    lv_style_set_text_font(&style_today_text, &lv_font_montserrat_18);
    lv_style_set_text_align(&style_today_text, LV_TEXT_ALIGN_CENTER);
    
    // ===== Activity Button - Dark background =====
    lv_style_init(&style_activity_btn);
    lv_style_set_bg_color(&style_activity_btn, COLOR_BTN_BG);
    lv_style_set_bg_opa(&style_activity_btn, LV_OPA_COVER);
    lv_style_set_radius(&style_activity_btn, 8);
    lv_style_set_border_width(&style_activity_btn, 0);
    lv_style_set_pad_ver(&style_activity_btn, 12);
    lv_style_set_pad_hor(&style_activity_btn, 40);
    
    // ===== Activity Text - Yellow =====
    lv_style_init(&style_activity_text);
    lv_style_set_text_color(&style_activity_text, COLOR_YELLOW);
    lv_style_set_text_font(&style_activity_text, &lv_font_montserrat_18);
    lv_style_set_text_align(&style_activity_text, LV_TEXT_ALIGN_CENTER);
}

/*===========================================================================
 * Style Getters
 *===========================================================================*/

lv_style_t* ui_style_bg(void)              { return &style_bg; }
lv_style_t* ui_style_timer_frame(void)     { return &style_timer_frame; }
lv_style_t* ui_style_timer_text(void)      { return &style_timer_text; }
lv_style_t* ui_style_timer_seconds(void)   { return &style_timer_seconds; }
lv_style_t* ui_style_today_text(void)      { return &style_today_text; }
lv_style_t* ui_style_activity_btn(void)    { return &style_activity_btn; }
lv_style_t* ui_style_activity_text(void)   { return &style_activity_text; }