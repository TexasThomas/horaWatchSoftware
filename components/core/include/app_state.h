#pragma once

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Application state - single source of truth
 * 
 * UI reads this state, logic modifies it.
 * UI never modifies state directly.
 */
typedef struct {
    // Time display (split for large digits)
    char date_str[8];          // "04-06" format
    char hour_str[4];          // "09" format
    char min_str[4];           // "40" format
    
    // Fitness stats
    uint32_t steps;            // Step count
    float kcal;                // Calories burned
    float km;                  // Distance in km
    
    // Device status
    uint8_t battery_pct;       // 0-100
    bool is_connected;         // BLE connected?
} app_state_t;

/**
 * @brief Initialize state with default values
 */
void app_state_init(app_state_t *state);
