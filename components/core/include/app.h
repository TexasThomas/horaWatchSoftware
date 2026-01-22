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
 * @brief Toggle category picker open/closed
 */
void app_toggle_picker(void);

/**
 * @brief Set current category and close picker
 */
void app_set_category(category_t cat);

/**
 * @brief Update timer display
 */
void app_update_timer(const char *hhmm, const char *ss);