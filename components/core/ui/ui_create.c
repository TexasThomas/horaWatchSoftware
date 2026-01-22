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
 *===========================================================================*/

void ui_create_home(ui_handle_t *ui)
{
    // Create home screen
    ui->scr_home = lv_obj_create(NULL);
    lv_obj_add_style(ui->scr_home, ui_style_bg(), 0);
    lv_obj_set_size(ui->scr_home, 240, 280);
    lv_obj_remove_flag(ui->scr_home, LV_OBJ_FLAG_SCROLLABLE);
    
    // ===== Timer Frame =====
    ui->timer_frame = lv_obj_create(ui->scr_home);
    lv_obj_add_style(ui->timer_frame, ui_style_timer_frame(), 0);
    lv_obj_set_size(ui->timer_frame, 210, 75);
    lv_obj_align(ui->timer_frame, LV_ALIGN_TOP_MID, 0, 35);
    lv_obj_remove_flag(ui->timer_frame, LV_OBJ_FLAG_SCROLLABLE);
    
    // Timer HH:MM
    ui->lbl_timer_hhmm = lv_label_create(ui->timer_frame);
    lv_obj_add_style(ui->lbl_timer_hhmm, ui_style_timer_text(), 0);
    lv_label_set_text(ui->lbl_timer_hhmm, "00:00");
    lv_obj_align(ui->lbl_timer_hhmm, LV_ALIGN_LEFT_MID, 10, 0);
    
    // Timer Seconds
    ui->lbl_timer_ss = lv_label_create(ui->timer_frame);
    lv_obj_add_style(ui->lbl_timer_ss, ui_style_timer_seconds(), 0);
    lv_label_set_text(ui->lbl_timer_ss, "00");
    lv_obj_align(ui->lbl_timer_ss, LV_ALIGN_RIGHT_MID, -12, 8);
    
    // ===== Today Total =====
    ui->lbl_today = lv_label_create(ui->scr_home);
    lv_obj_add_style(ui->lbl_today, ui_style_today_text(), 0);
    lv_label_set_text(ui->lbl_today, "Today: 2:13:10");
    lv_obj_align(ui->lbl_today, LV_ALIGN_CENTER, 0, 10);
    
    // ===== Activity Button =====
    ui->btn_activity = lv_button_create(ui->scr_home);
    lv_obj_add_style(ui->btn_activity, ui_style_activity_btn(), 0);
    lv_obj_set_size(ui->btn_activity, 140, 48);
    lv_obj_align(ui->btn_activity, LV_ALIGN_BOTTOM_MID, 0, -40);
    
    ui->lbl_activity = lv_label_create(ui->btn_activity);
    lv_label_set_text(ui->lbl_activity, "Reading");
    lv_obj_set_style_text_color(ui->lbl_activity, lv_color_hex(0xE5A800), 0);
    lv_obj_set_style_text_font(ui->lbl_activity, &lv_font_montserrat_18, 0);
    lv_obj_center(ui->lbl_activity);
    
    // ===== Category Picker (hidden initially) =====
    ui->picker_container = lv_obj_create(ui->scr_home);
    lv_obj_add_style(ui->picker_container, ui_style_picker_frame(), 0);
    lv_obj_set_size(ui->picker_container, 200, 145);
    lv_obj_align(ui->picker_container, LV_ALIGN_TOP_MID, 0, 30);
    lv_obj_remove_flag(ui->picker_container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui->picker_container, LV_OBJ_FLAG_HIDDEN);  // Hidden by default
    
    // Reading option (Yellow)
    ui->btn_reading = lv_button_create(ui->picker_container);
    lv_obj_add_style(ui->btn_reading, ui_style_picker_item(), 0);
    lv_obj_set_size(ui->btn_reading, 180, 40);
    lv_obj_align(ui->btn_reading, LV_ALIGN_TOP_MID, 0, 0);
    
    ui->lbl_reading = lv_label_create(ui->btn_reading);
    lv_label_set_text(ui->lbl_reading, "Reading");
    lv_obj_set_style_text_color(ui->lbl_reading, lv_color_hex(0xE5A800), 0);
    lv_obj_set_style_text_font(ui->lbl_reading, &lv_font_montserrat_18, 0);
    lv_obj_center(ui->lbl_reading);
    
    // Business option (Red)
    ui->btn_business = lv_button_create(ui->picker_container);
    lv_obj_add_style(ui->btn_business, ui_style_picker_item(), 0);
    lv_obj_set_size(ui->btn_business, 180, 40);
    lv_obj_align(ui->btn_business, LV_ALIGN_TOP_MID, 0, 45);
    
    ui->lbl_business = lv_label_create(ui->btn_business);
    lv_label_set_text(ui->lbl_business, "Business");
    lv_obj_set_style_text_color(ui->lbl_business, lv_color_hex(0xFF3B30), 0);
    lv_obj_set_style_text_font(ui->lbl_business, &lv_font_montserrat_18, 0);
    lv_obj_center(ui->lbl_business);
    
    // Studying option (Green)
    ui->btn_studying = lv_button_create(ui->picker_container);
    lv_obj_add_style(ui->btn_studying, ui_style_picker_item(), 0);
    lv_obj_set_size(ui->btn_studying, 180, 40);
    lv_obj_align(ui->btn_studying, LV_ALIGN_TOP_MID, 0, 90);
    
    ui->lbl_studying = lv_label_create(ui->btn_studying);
    lv_label_set_text(ui->lbl_studying, "Studying");
    lv_obj_set_style_text_color(ui->lbl_studying, lv_color_hex(0x30D158), 0);
    lv_obj_set_style_text_font(ui->lbl_studying, &lv_font_montserrat_18, 0);
    lv_obj_center(ui->lbl_studying);
    
    ESP_LOGI(TAG, "Home screen created with category picker");
}

/*===========================================================================
 * Show/Hide Picker
 *===========================================================================*/

void ui_show_picker(bool show)
{
    ui_handle_t *ui = ui_get_handle();
    
    if (show) {
        // Hide timer frame, show picker
        lv_obj_add_flag(ui->timer_frame, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui->lbl_today, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(ui->picker_container, LV_OBJ_FLAG_HIDDEN);
    } else {
        // Show timer frame, hide picker
        lv_obj_remove_flag(ui->timer_frame, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(ui->lbl_today, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui->picker_container, LV_OBJ_FLAG_HIDDEN);
    }
}

/*===========================================================================
 * Update Category Colors
 *===========================================================================*/

void ui_update_category_colors(category_t cat)
{
    ui_handle_t *ui = ui_get_handle();
    uint32_t color = app_get_category_color(cat);
    
    // Update Today label color
    lv_obj_set_style_text_color(ui->lbl_today, lv_color_hex(color), 0);
    
    // Update activity button text color
    lv_obj_set_style_text_color(ui->lbl_activity, lv_color_hex(color), 0);
}