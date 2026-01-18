#pragma once
#include "lvgl.h"

typedef struct {
    lv_obj_t *label;
} ui_t;

void ui_init(ui_t *ui);
void ui_tick(ui_t *ui);

