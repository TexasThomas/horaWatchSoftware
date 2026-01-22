#include "ui.h"
#include "esp_log.h"

static const char *TAG = "ui_create";

/*===========================================================================
 * Global UI Handle
 *===========================================================================*/
static ui_handle_t s_ui;

ui_handle_t* ui_get_handle(void)
{
    return &s_ui;
}

/*===========================================================================
 * UI Initialization
 *===========================================================================*/

void ui_init(void)
{
    ESP_LOGI(TAG, "Initializing UI (240x280)");
    
    ui_styles_init();
    ui_create_home(&s_ui);
    ui_events_init(&s_ui);
    lv_screen_load(s_ui.scr_home);
    
    ESP_LOGI(TAG, "UI initialization complete");
}

/*===========================================================================
 * Home Screen Creation
 * 
 * Layout (240x280) - Exact match to reference image:
 * 
 *   ┌────────────────────────────────────┐
 *   │                                    │
 *   │   ┌──────────────────────────┐     │
 *   │   │    00:00          00     │     │  Cyan frame + timer
 *   │   └──────────────────────────┘     │
 *   │                                    │
 *   │         Today: 2:13:10             │  Yellow text
 *   │                                    │
 *   │          [ Reading ]               │  Yellow button
 *   │                                    │
 *   └────────────────────────────────────┘
 * 
 *===========================================================================*/

void ui_create_home(ui_handle_t *ui)
{
    // Create home screen
    ui->scr_home = lv_obj_create(NULL);
    lv_obj_add_style(ui->scr_home, ui_style_bg(), 0);
    lv_obj_set_size(ui->scr_home, 240, 280);
    lv_obj_remove_flag(ui->scr_home, LV_OBJ_FLAG_SCROLLABLE);
    
    // ===== Timer Frame (cyan border box) =====
    ui->timer_frame = lv_obj_create(ui->scr_home);
    lv_obj_add_style(ui->timer_frame, ui_style_timer_frame(), 0);
    lv_obj_set_size(ui->timer_frame, 210, 75);
    lv_obj_align(ui->timer_frame, LV_ALIGN_TOP_MID, 0, 35);
    lv_obj_remove_flag(ui->timer_frame, LV_OBJ_FLAG_SCROLLABLE);
    
    // ===== Timer HH:MM (big cyan text inside frame) =====
    ui->lbl_timer_hhmm = lv_label_create(ui->timer_frame);
    lv_obj_add_style(ui->lbl_timer_hhmm, ui_style_timer_text(), 0);
    lv_label_set_text(ui->lbl_timer_hhmm, "00:00");
    lv_obj_align(ui->lbl_timer_hhmm, LV_ALIGN_LEFT_MID, 10, 0);
    
    // ===== Timer Seconds (small cyan, subscript position) =====
    ui->lbl_timer_ss = lv_label_create(ui->timer_frame);
    lv_obj_add_style(ui->lbl_timer_ss, ui_style_timer_seconds(), 0);
    lv_label_set_text(ui->lbl_timer_ss, "00");
    lv_obj_align(ui->lbl_timer_ss, LV_ALIGN_RIGHT_MID, -12, 8);
    
    // ===== Today Total (yellow text) =====
    ui->lbl_today = lv_label_create(ui->scr_home);
    lv_obj_add_style(ui->lbl_today, ui_style_today_text(), 0);
    lv_label_set_text(ui->lbl_today, "Today: 2:13:10");
    lv_obj_align(ui->lbl_today, LV_ALIGN_CENTER, 0, 10);
    
    // ===== Activity Button =====
    ui->btn_activity = lv_button_create(ui->scr_home);
    lv_obj_add_style(ui->btn_activity, ui_style_activity_btn(), 0);
    lv_obj_set_size(ui->btn_activity, 140, 48);
    lv_obj_align(ui->btn_activity, LV_ALIGN_BOTTOM_MID, 0, -40);
    
    // Activity label inside button
    ui->lbl_activity = lv_label_create(ui->btn_activity);
    lv_obj_add_style(ui->lbl_activity, ui_style_activity_text(), 0);
    lv_label_set_text(ui->lbl_activity, "Reading");
    lv_obj_center(ui->lbl_activity);
    
    ESP_LOGI(TAG, "Home screen created - timer style");
}