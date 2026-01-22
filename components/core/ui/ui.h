#pragma once

#include "lvgl.h"
#include "app_state.h"

/*===========================================================================
 * UI Handle Structure
 *===========================================================================*/
typedef struct {
    lv_obj_t *scr_home;
    
    // Timer frame (cyan border box)
    lv_obj_t *timer_frame;
    
    // Timer display inside frame
    lv_obj_t *lbl_timer_hhmm;      // "00:00" big cyan
    lv_obj_t *lbl_timer_ss;        // "00" small cyan (seconds)
    
    // Today total (color changes with category)
    lv_obj_t *lbl_today;           // "Today: 2:13:10"
    
    // Activity button
    lv_obj_t *btn_activity;
    lv_obj_t *lbl_activity;        // "Reading"
    
    // Category picker popup
    lv_obj_t *picker_container;    // Cyan frame container
    lv_obj_t *btn_reading;
    lv_obj_t *lbl_reading;
    lv_obj_t *btn_business;
    lv_obj_t *lbl_business;
    lv_obj_t *btn_studying;
    lv_obj_t *lbl_studying;
} ui_handle_t;

/*===========================================================================
 * UI Functions
 *===========================================================================*/
void ui_init(void);
ui_handle_t* ui_get_handle(void);

/*===========================================================================
 * Styles
 *===========================================================================*/
void ui_styles_init(void);

lv_style_t* ui_style_bg(void);
lv_style_t* ui_style_timer_frame(void);
lv_style_t* ui_style_timer_text(void);
lv_style_t* ui_style_timer_seconds(void);
lv_style_t* ui_style_today_text(void);
lv_style_t* ui_style_activity_btn(void);
lv_style_t* ui_style_picker_frame(void);
lv_style_t* ui_style_picker_item(void);

/*===========================================================================
 * Create / Bindings / Events
 *===========================================================================*/
void ui_create_home(ui_handle_t *ui);
void ui_bind_home(const app_state_t *state);
void ui_events_init(ui_handle_t *ui);

/**
 * @brief Show/hide category picker
 */
void ui_show_picker(bool show);

/**
 * @brief Update colors based on category
 */
void ui_update_category_colors(category_t cat);