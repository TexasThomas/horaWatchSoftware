#include "app_state.h"
#include <string.h>

// Category names
static const char* category_names[CATEGORY_COUNT] = {
    "Reading",
    "Business", 
    "Studying"
};

// Category colors (hex)
static const uint32_t category_colors[CATEGORY_COUNT] = {
    0xE5A800,  // Reading - Yellow/Gold
    0xFF3B30,  // Business - Red
    0x30D158   // Studying - Green
};

void app_state_init(app_state_t *state)
{
    // Timer display
    strcpy(state->timer_hhmm, "00:00");
    strcpy(state->timer_ss, "00");
    
    // Today totals (different per category)
    strcpy(state->today_total[CATEGORY_READING], "2:13:10");
    strcpy(state->today_total[CATEGORY_BUSINESS], "1:45:30");
    strcpy(state->today_total[CATEGORY_STUDYING], "3:22:15");
    
    // Default category
    state->current_category = CATEGORY_READING;
    
    // State
    state->is_running = false;
    state->picker_open = false;
    state->battery_pct = 100;
}

const char* app_get_category_name(category_t cat)
{
    if (cat < CATEGORY_COUNT) {
        return category_names[cat];
    }
    return "Unknown";
}

uint32_t app_get_category_color(category_t cat)
{
    if (cat < CATEGORY_COUNT) {
        return category_colors[cat];
    }
    return 0xFFFFFF;
}