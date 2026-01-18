idf_component_register(
    SRCS
        "app.c"
        "app_state.c"
        "ui/ui_create.c"
        "ui/test.c"  # Alexander the Great image (200x200)
    INCLUDE_DIRS
        "include"
        "ui"
    REQUIRES
        lvgl
)
