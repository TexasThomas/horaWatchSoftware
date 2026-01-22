#pragma once

#include "app_state.h"

/**
 * @brief Initialize the application
 */
void app_init(void);

/**
 * @brief Get pointer to app state
 */
app_state_t* app_get_state(void);

/**
 * @brief Update timer display
 */
void app_update_timer(const char *hhmm, const char *ss);

/**
 * @brief Update today total
 */
void app_update_today(const char *total);

/**
 * @brief Set activity name
 */
void app_set_activity(const char *name);