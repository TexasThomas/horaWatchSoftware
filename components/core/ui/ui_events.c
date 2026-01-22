#include "ui.h"
#include "app.h"
#include "esp_log.h"

static const char *TAG = "ui_events";

/*===========================================================================
 * Event Handlers
 *===========================================================================*/

// Open picker when activity button is clicked
static void activity_btn_click_cb(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "Activity button clicked - opening picker");
    app_toggle_picker();
}

// Select Reading category
static void reading_click_cb(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "Reading selected");
    app_set_category(CATEGORY_READING);
}

// Select Business category
static void business_click_cb(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "Business selected");
    app_set_category(CATEGORY_BUSINESS);
}

// Select Studying category
static void studying_click_cb(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "Studying selected");
    app_set_category(CATEGORY_STUDYING);
}

void ui_events_init(ui_handle_t *ui)
{
    // Activity button opens picker
    lv_obj_add_event_cb(ui->btn_activity, activity_btn_click_cb, LV_EVENT_CLICKED, NULL);
    
    // Category selection buttons
    lv_obj_add_event_cb(ui->btn_reading, reading_click_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui->btn_business, business_click_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui->btn_studying, studying_click_cb, LV_EVENT_CLICKED, NULL);
}