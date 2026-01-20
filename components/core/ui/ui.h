#pragma once

#include "lvgl.h"
#include "app_state.h"

/*===========================================================================
 * UI Handle Structure - holds all UI object references
 *===========================================================================*/
typedef struct {
    // Home screen
    lv_obj_t *scr_home;
    
    // Date (top center)
    lv_obj_t *lbl_date;
    
    // Big time display (left side, stacked)
    lv_obj_t *lbl_hour;           // "09" - huge green
    lv_obj_t *lbl_min;            // "40" - huge green
    
    // Stats panels (right side)
    lv_obj_t *panel_steps;
    lv_obj_t *lbl_steps_value;    // "10349"
    lv_obj_t *lbl_steps_unit;     // "STEP"
    
    lv_obj_t *panel_kcal;
    lv_obj_t *lbl_kcal_value;     // "103.4"
    lv_obj_t *lbl_kcal_unit;      // "KCAL"
    
    lv_obj_t *panel_km;
    lv_obj_t *lbl_km_value;       // "103.4"
    lv_obj_t *lbl_km_unit;        // "KM"
    
    // Battery (bottom left)
    lv_obj_t *lbl_battery;        // "100%"
} ui_handle_t;

/*===========================================================================
 * UI Functions
 *===========================================================================*/

/**
 * @brief Initialize UI (styles + create screens)
 */
void ui_init(void);

/**
 * @brief Get UI handle (for internal use)
 */
ui_handle_t* ui_get_handle(void);

/*===========================================================================
 * Styles (ui_styles.c)
 *===========================================================================*/

/**
 * @brief Initialize all styles
 */
void ui_styles_init(void);

// Style getters
lv_style_t* ui_style_bg(void);
lv_style_t* ui_style_time_big(void);      // Huge green digits
lv_style_t* ui_style_date(void);          // Date at top
lv_style_t* ui_style_stat_panel(void);    // Dark rounded panel
lv_style_t* ui_style_stat_value(void);    // White stat numbers
lv_style_t* ui_style_stat_unit(void);     // Gray unit labels
lv_style_t* ui_style_battery(void);       // Cyan battery text

/*===========================================================================
 * Create (ui_create.c)
 *===========================================================================*/

/**
 * @brief Create home screen layout
 */
void ui_create_home(ui_handle_t *ui);

/*===========================================================================
 * Bindings (ui_bindings.c)
 *===========================================================================*/

/**
 * @brief Bind state to home screen
 */
void ui_bind_home(const app_state_t *state);

/*===========================================================================
 * Events (ui_events.c)
 *===========================================================================*/

/**
 * @brief Setup event handlers
 */
void ui_events_init(ui_handle_t *ui);
