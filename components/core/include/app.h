#pragma once

#include "app_state.h"
#include <stdint.h>

/**
 * @brief Initialize the application
 * 
 * Creates UI, initializes state, sets up bindings.
 */
void app_init(void);

/**
 * @brief Get pointer to app state (for UI bindings)
 */
app_state_t* app_get_state(void);

/**
 * @brief Update time display
 */
void app_update_time(const char *hour, const char *min);

/**
 * @brief Update fitness stats
 */
void app_update_stats(uint32_t steps, float kcal, float km);
