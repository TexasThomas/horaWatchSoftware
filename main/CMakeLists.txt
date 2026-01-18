idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS "."
    REQUIRES esp_timer lvgl bsp core
)

target_compile_definitions(${COMPONENT_LIB} PRIVATE LV_CONF_INCLUDE_SIMPLE=1)
target_include_directories(${COMPONENT_LIB} PRIVATE "${CMAKE_SOURCE_DIR}")
