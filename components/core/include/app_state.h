#pragma once

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Application state - single source of truth
 */
typedef struct {
    // Timer display (current session)
    char timer_hhmm[8];        // "00:00" format
    char timer_ss[4];          // "00" seconds
    
    // Today total
    char today_total[16];      // "2:13:10" format
    
    // Current activity
    char activity_name[16];    // "Reading", "Working", etc.
    
    // Session state
    bool is_running;
    
    // Device status
    uint8_t battery_pct;
} app_state_t;

/**
 * @brief Initialize state with default values
 */
void app_state_init(app_state_t *state);