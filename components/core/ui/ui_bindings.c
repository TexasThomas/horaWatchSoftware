#include "ui.h"
#include <stdio.h>

/*===========================================================================
 * Home Screen Bindings
 * 
 * Maps app_state_t fields to UI elements.
 * This is the ONLY place where state writes to UI.
 *===========================================================================*/

void ui_bind_home(const app_state_t *state)
{
    ui_handle_t *ui = ui_get_handle();
    
    // ===== Date =====
    lv_label_set_text(ui->lbl_date, state->date_str);
    
    // ===== Time (Hours & Minutes) =====
    lv_label_set_text(ui->lbl_hour, state->hour_str);
    lv_label_set_text(ui->lbl_min, state->min_str);
    
    // ===== Steps =====
    char steps_str[16];
    snprintf(steps_str, sizeof(steps_str), "%lu", (unsigned long)state->steps);
    lv_label_set_text(ui->lbl_steps_value, steps_str);
    
    // ===== Kcal =====
    char kcal_str[16];
    snprintf(kcal_str, sizeof(kcal_str), "%.1f", state->kcal);
    lv_label_set_text(ui->lbl_kcal_value, kcal_str);
    
    // ===== KM =====
    char km_str[16];
    snprintf(km_str, sizeof(km_str), "%.1f", state->km);
    lv_label_set_text(ui->lbl_km_value, km_str);
    
    // ===== Battery =====
    char bat_str[16];
    snprintf(bat_str, sizeof(bat_str), LV_SYMBOL_CHARGE " %d%%", state->battery_pct);
    lv_label_set_text(ui->lbl_battery, bat_str);
}
