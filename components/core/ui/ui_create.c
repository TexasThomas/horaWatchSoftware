#include "ui.h"

// External declaration for test image (Alexander the Great from test.c)
extern const lv_image_dsc_t test;

void ui_init(ui_t *ui)
{
    lv_obj_t *scr = lv_screen_active();
    
    // Create image widget with test image
    lv_obj_t *img = lv_image_create(scr);
    lv_image_set_src(img, &test);
    
    // Image is 200x200, center it
    lv_obj_center(img);
    
    // Store reference in ui struct (can be NULL if we don't need label)
    ui->label = NULL;
}

void ui_tick(ui_t *ui)
{
    (void)ui;
}

