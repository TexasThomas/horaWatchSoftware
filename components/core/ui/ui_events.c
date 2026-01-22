#include "ui.h"
#include "app.h"

/*===========================================================================
 * Event Handlers
 *===========================================================================*/

static void activity_btn_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        // TODO: Handle activity button click
        // Could switch activity or open activity picker
    }
}

void ui_events_init(ui_handle_t *ui)
{
    // Activity button click handler
    lv_obj_add_event_cb(ui->btn_activity, activity_btn_event_cb, LV_EVENT_CLICKED, NULL);
}