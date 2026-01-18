#include "ui.h"

void ui_init(ui_t *ui)
{
    lv_obj_t *scr = lv_screen_active();
    ui->label = lv_label_create(scr);
    lv_label_set_text(ui->label, "Hello LVGL");
    lv_obj_center(ui->label);
}

void ui_tick(ui_t *ui)
{
    (void)ui;
}

