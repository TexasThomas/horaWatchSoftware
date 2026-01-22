#include "ui.h"
#include <stdio.h>

/*===========================================================================
 * Home Screen Bindings
 *===========================================================================*/

void ui_bind_home(const app_state_t *state)
{
    ui_handle_t *ui = ui_get_handle();
    
    // Timer display
    lv_label_set_text(ui->lbl_timer_hhmm, state->timer_hhmm);
    lv_label_set_text(ui->lbl_timer_ss, state->timer_ss);
    
    // Today total
    char today_str[32];
    snprintf(today_str, sizeof(today_str), "Today: %s", state->today_total);
    lv_label_set_text(ui->lbl_today, today_str);
    
    // Activity button
    lv_label_set_text(ui->lbl_activity, state->activity_name);
}