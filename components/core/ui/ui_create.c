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
    ESP_LOGI(TAG, "Initializing UI (240x280, RGB565)");
    
    // Initialize styles first
    ui_styles_init();
    
    // Create home screen
    ui_create_home(&s_ui);
    
    // Setup event handlers
    ui_events_init(&s_ui);
    
    // Load home screen
    lv_screen_load(s_ui.scr_home);
    
    ESP_LOGI(TAG, "UI initialization complete");
}

/*===========================================================================
 * Home Screen Creation
 * 
 * Layout (240x280) - Like reference image:
 * 
 *   ┌────────────────────────────────────┐
 *   │          04-06           ← Date    │
 *   │                         ┌────────┐ │
 *   │   09                    │ 10349  │ │  Steps
 *   │                         │  STEP  │ │
 *   │                         ├────────┤ │
 *   │                         │ 103.4  │ │  Kcal
 *   │   40                    │  KCAL  │ │
 *   │                         ├────────┤ │
 *   │                         │ 103.4  │ │  KM
 *   │                         │   KM   │ │
 *   │                         └────────┘ │
 *   │  ⚡ 100%                            │
 *   └────────────────────────────────────┘
 * 
 *===========================================================================*/

void ui_create_home(ui_handle_t *ui)
{
    // Create home screen with pure black background
    ui->scr_home = lv_obj_create(NULL);
    lv_obj_add_style(ui->scr_home, ui_style_bg(), 0);
    lv_obj_set_size(ui->scr_home, 240, 280);
    lv_obj_remove_flag(ui->scr_home, LV_OBJ_FLAG_SCROLLABLE);
    
    // ===== Date (top center) =====
    ui->lbl_date = lv_label_create(ui->scr_home);
    lv_obj_add_style(ui->lbl_date, ui_style_date(), 0);
    lv_label_set_text(ui->lbl_date, "04-06");
    lv_obj_align(ui->lbl_date, LV_ALIGN_TOP_MID, -20, 12);
    
    // ===== Big Time - HOURS (left side, top) =====
    ui->lbl_hour = lv_label_create(ui->scr_home);
    lv_obj_add_style(ui->lbl_hour, ui_style_time_big(), 0);
    lv_label_set_text(ui->lbl_hour, "09");
    lv_obj_set_pos(ui->lbl_hour, 16, 45);
    // Make it even bigger with custom font size
    lv_obj_set_style_text_font(ui->lbl_hour, &lv_font_montserrat_48, 0);
    
    // ===== Big Time - MINUTES (left side, below hours) =====
    ui->lbl_min = lv_label_create(ui->scr_home);
    lv_obj_add_style(ui->lbl_min, ui_style_time_big(), 0);
    lv_label_set_text(ui->lbl_min, "40");
    lv_obj_set_pos(ui->lbl_min, 16, 135);
    lv_obj_set_style_text_font(ui->lbl_min, &lv_font_montserrat_48, 0);
    
    // ===== Stats Panels (right side) =====
    
    // --- Steps Panel ---
    ui->panel_steps = lv_obj_create(ui->scr_home);
    lv_obj_add_style(ui->panel_steps, ui_style_stat_panel(), 0);
    lv_obj_set_size(ui->panel_steps, 85, 55);
    lv_obj_set_pos(ui->panel_steps, 145, 40);
    lv_obj_remove_flag(ui->panel_steps, LV_OBJ_FLAG_SCROLLABLE);
    
    ui->lbl_steps_value = lv_label_create(ui->panel_steps);
    lv_obj_add_style(ui->lbl_steps_value, ui_style_stat_value(), 0);
    lv_label_set_text(ui->lbl_steps_value, "10349");
    lv_obj_align(ui->lbl_steps_value, LV_ALIGN_CENTER, 0, -6);
    
    ui->lbl_steps_unit = lv_label_create(ui->panel_steps);
    lv_obj_add_style(ui->lbl_steps_unit, ui_style_stat_unit(), 0);
    lv_label_set_text(ui->lbl_steps_unit, "STEP");
    lv_obj_align(ui->lbl_steps_unit, LV_ALIGN_CENTER, 0, 12);
    
    // --- Kcal Panel ---
    ui->panel_kcal = lv_obj_create(ui->scr_home);
    lv_obj_add_style(ui->panel_kcal, ui_style_stat_panel(), 0);
    lv_obj_set_size(ui->panel_kcal, 85, 55);
    lv_obj_set_pos(ui->panel_kcal, 145, 105);
    lv_obj_remove_flag(ui->panel_kcal, LV_OBJ_FLAG_SCROLLABLE);
    
    ui->lbl_kcal_value = lv_label_create(ui->panel_kcal);
    lv_obj_add_style(ui->lbl_kcal_value, ui_style_stat_value(), 0);
    lv_label_set_text(ui->lbl_kcal_value, "103.4");
    lv_obj_align(ui->lbl_kcal_value, LV_ALIGN_CENTER, 0, -6);
    
    ui->lbl_kcal_unit = lv_label_create(ui->panel_kcal);
    lv_obj_add_style(ui->lbl_kcal_unit, ui_style_stat_unit(), 0);
    lv_label_set_text(ui->lbl_kcal_unit, "KCAL");
    lv_obj_align(ui->lbl_kcal_unit, LV_ALIGN_CENTER, 0, 12);
    
    // --- KM Panel ---
    ui->panel_km = lv_obj_create(ui->scr_home);
    lv_obj_add_style(ui->panel_km, ui_style_stat_panel(), 0);
    lv_obj_set_size(ui->panel_km, 85, 55);
    lv_obj_set_pos(ui->panel_km, 145, 170);
    lv_obj_remove_flag(ui->panel_km, LV_OBJ_FLAG_SCROLLABLE);
    
    ui->lbl_km_value = lv_label_create(ui->panel_km);
    lv_obj_add_style(ui->lbl_km_value, ui_style_stat_value(), 0);
    lv_label_set_text(ui->lbl_km_value, "103.4");
    lv_obj_align(ui->lbl_km_value, LV_ALIGN_CENTER, 0, -6);
    
    ui->lbl_km_unit = lv_label_create(ui->panel_km);
    lv_obj_add_style(ui->lbl_km_unit, ui_style_stat_unit(), 0);
    lv_label_set_text(ui->lbl_km_unit, "KM");
    lv_obj_align(ui->lbl_km_unit, LV_ALIGN_CENTER, 0, 12);
    
    // ===== Battery (bottom left) =====
    ui->lbl_battery = lv_label_create(ui->scr_home);
    lv_obj_add_style(ui->lbl_battery, ui_style_battery(), 0);
    lv_label_set_text(ui->lbl_battery, LV_SYMBOL_CHARGE " 100%");
    lv_obj_set_pos(ui->lbl_battery, 16, 245);
    
    ESP_LOGI(TAG, "Home screen created - smartwatch style");
}
