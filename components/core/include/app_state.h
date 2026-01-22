#pragma once

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Category types with associated colors
 */
typedef enum {
    CATEGORY_READING = 0,   // Yellow
    CATEGORY_BUSINESS,      // Red
    CATEGORY_STUDYING,      // Green
    CATEGORY_COUNT
} category_t;

/**
 * @brief Application state - single source of truth
 */
typedef struct {
    // Timer display (current session)
    char timer_hhmm[8];        // "00:00" format
    char timer_ss[4];          // "00" seconds
    
    // Today total per category
    char today_total[CATEGORY_COUNT][16];  // Different time per category
    
    // Current category
    category_t current_category;
    
    // Session state
    bool is_running;
    bool picker_open;          // Category picker visible?
    
    // Device status
    uint8_t battery_pct;
} app_state_t;

/**
 * @brief Initialize state with default values
 */
void app_state_init(app_state_t *state);

/**
 * @brief Get category name
 */
const char* app_get_category_name(category_t cat);

/**
 * @brief Get category color (as hex)
 */
uint32_t app_get_category_color(category_t cat);