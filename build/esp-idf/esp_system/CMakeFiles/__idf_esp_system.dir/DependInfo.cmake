
# Consider dependencies only in project.
set(CMAKE_DEPENDS_IN_PROJECT_ONLY OFF)

# The set of languages for which implicit dependencies are needed:
set(CMAKE_DEPENDS_LANGUAGES
  "ASM"
  )
# The set of files for implicit dependencies of each language:
set(CMAKE_DEPENDS_CHECK_ASM
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/arch/xtensa/debug_helpers_asm.S" "/Users/markgrun/Watch18.1/horaWatchSoftware/build/esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/arch/xtensa/debug_helpers_asm.S.obj"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/arch/xtensa/esp_ipc_isr_handler.S" "/Users/markgrun/Watch18.1/horaWatchSoftware/build/esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/arch/xtensa/esp_ipc_isr_handler.S.obj"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/arch/xtensa/esp_ipc_isr_routines.S" "/Users/markgrun/Watch18.1/horaWatchSoftware/build/esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/arch/xtensa/esp_ipc_isr_routines.S.obj"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/arch/xtensa/expression_with_stack_asm.S" "/Users/markgrun/Watch18.1/horaWatchSoftware/build/esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/arch/xtensa/expression_with_stack_asm.S.obj"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/arch/xtensa/panic_handler_asm.S" "/Users/markgrun/Watch18.1/horaWatchSoftware/build/esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/arch/xtensa/panic_handler_asm.S.obj"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/soc/esp32/highint_hdl.S" "/Users/markgrun/Watch18.1/horaWatchSoftware/build/esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/soc/esp32/highint_hdl.S.obj"
  )
set(CMAKE_ASM_COMPILER_ID "GNU")

# Preprocessor definitions for this target.
set(CMAKE_TARGET_DEFINITIONS_ASM
  "ESP_PLATFORM"
  "IDF_VER=\"v6.1-dev-2002-gfa47e101d5\""
  "SOC_MMU_PAGE_SIZE=CONFIG_MMU_PAGE_SIZE"
  "SOC_XTAL_FREQ_MHZ=CONFIG_XTAL_FREQ"
  "_GLIBCXX_HAVE_POSIX_SEMAPHORE"
  "_GLIBCXX_USE_POSIX_SEMAPHORE"
  "_GNU_SOURCE"
  "_POSIX_READER_WRITER_LOCKS"
  )

# The include file search paths:
set(CMAKE_ASM_TARGET_INCLUDE_PATH
  "config"
  "/Users/markgrun/esp/esp-idf/components/esp_system/include"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/include"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/."
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/soc"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/include/private"
  "/Users/markgrun/esp/esp-idf/components/esp_libc/platform_include"
  "/Users/markgrun/esp/esp-idf/components/freertos/config/include"
  "/Users/markgrun/esp/esp-idf/components/freertos/config/include/freertos"
  "/Users/markgrun/esp/esp-idf/components/freertos/config/xtensa/include"
  "/Users/markgrun/esp/esp-idf/components/freertos/FreeRTOS-Kernel/include"
  "/Users/markgrun/esp/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include"
  "/Users/markgrun/esp/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos"
  "/Users/markgrun/esp/esp-idf/components/freertos/esp_additions/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hw_support/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hw_support/include/soc"
  "/Users/markgrun/esp/esp-idf/components/esp_hw_support/dma/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hw_support/ldo/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hw_support/debug_probe/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hw_support/etm/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hw_support/mspi/mspi_timing_tuning/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hw_support/mspi/mspi_timing_tuning/tuning_scheme_impl/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hw_support/mspi/mspi_intr/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hw_support/power_supply/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hw_support/modem/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hw_support/port/esp32/."
  "/Users/markgrun/esp/esp-idf/components/esp_hw_support/port/esp32/include"
  "/Users/markgrun/esp/esp-idf/components/heap/include"
  "/Users/markgrun/esp/esp-idf/components/heap/tlsf"
  "/Users/markgrun/esp/esp-idf/components/log/include"
  "/Users/markgrun/esp/esp-idf/components/soc/include"
  "/Users/markgrun/esp/esp-idf/components/soc/esp32"
  "/Users/markgrun/esp/esp-idf/components/soc/esp32/include"
  "/Users/markgrun/esp/esp-idf/components/soc/esp32/register"
  "/Users/markgrun/esp/esp-idf/components/hal/platform_port/include"
  "/Users/markgrun/esp/esp-idf/components/hal/esp32/include"
  "/Users/markgrun/esp/esp-idf/components/hal/include"
  "/Users/markgrun/esp/esp-idf/components/esp_rom/include"
  "/Users/markgrun/esp/esp-idf/components/esp_rom/esp32/include"
  "/Users/markgrun/esp/esp-idf/components/esp_rom/esp32/include/esp32"
  "/Users/markgrun/esp/esp-idf/components/esp_rom/esp32"
  "/Users/markgrun/esp/esp-idf/components/esp_common/include"
  "/Users/markgrun/esp/esp-idf/components/esp_stdio/include"
  "/Users/markgrun/esp/esp-idf/components/xtensa/esp32/include"
  "/Users/markgrun/esp/esp-idf/components/xtensa/include"
  "/Users/markgrun/esp/esp-idf/components/xtensa/deprecated_include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_dma/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_gpio/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_gpio/esp32/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_usb/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_pmu/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_pmu/esp32/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_ana_conv/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_ana_conv/esp32/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_i2s/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_i2s/esp32/include"
  "/Users/markgrun/esp/esp-idf/components/spi_flash/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_mspi/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_mspi/esp32/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_gpspi/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_gpspi/esp32/include"
  "/Users/markgrun/esp/esp-idf/components/esp_blockdev/include"
  "/Users/markgrun/esp/esp-idf/components/esp_timer/include"
  "/Users/markgrun/esp/esp-idf/components/esp_mm/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_wdt/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_wdt/esp32/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_timg/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_timg/esp32/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_uart/include"
  "/Users/markgrun/esp/esp-idf/components/esp_hal_uart/esp32/include"
  "/Users/markgrun/esp/esp-idf/components/bootloader_support/include"
  "/Users/markgrun/esp/esp-idf/components/bootloader_support/bootloader_flash/include"
  "/Users/markgrun/esp/esp-idf/components/esp_pm/include"
  "/Users/markgrun/esp/esp-idf/components/esp_usb_cdc_rom_console/include"
  "/Users/markgrun/esp/esp-idf/components/esp_app_format/include"
  )

# The set of dependency files which are needed:
set(CMAKE_DEPENDS_DEPENDENCY_FILES
  "/Users/markgrun/esp/esp-idf/components/esp_system/crosscore_int.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/crosscore_int.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/crosscore_int.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/esp_err.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/esp_err.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/esp_err.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/esp_ipc.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/esp_ipc.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/esp_ipc.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/esp_system.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/esp_system.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/esp_system.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/freertos_hooks.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/freertos_hooks.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/freertos_hooks.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/int_wdt.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/int_wdt.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/int_wdt.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/panic.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/panic.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/panic.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/arch/xtensa/debug_helpers.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/arch/xtensa/debug_helpers.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/arch/xtensa/debug_helpers.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/arch/xtensa/debug_stubs.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/arch/xtensa/debug_stubs.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/arch/xtensa/debug_stubs.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/arch/xtensa/esp_ipc_isr_port.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/arch/xtensa/esp_ipc_isr_port.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/arch/xtensa/esp_ipc_isr_port.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/arch/xtensa/expression_with_stack.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/arch/xtensa/expression_with_stack.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/arch/xtensa/expression_with_stack.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/arch/xtensa/panic_arch.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/arch/xtensa/panic_arch.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/arch/xtensa/panic_arch.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/arch/xtensa/trax.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/arch/xtensa/trax.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/arch/xtensa/trax.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/cpu_start.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/cpu_start.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/cpu_start.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/esp_ipc_isr.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/esp_ipc_isr.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/esp_ipc_isr.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/esp_system_chip.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/esp_system_chip.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/esp_system_chip.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/image_process.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/image_process.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/image_process.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/panic_handler.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/panic_handler.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/panic_handler.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/soc/esp32/cache_err_int.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/soc/esp32/cache_err_int.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/soc/esp32/cache_err_int.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/soc/esp32/clk.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/soc/esp32/clk.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/soc/esp32/clk.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/soc/esp32/reset_reason.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/soc/esp32/reset_reason.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/soc/esp32/reset_reason.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/port/soc/esp32/system_internal.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/soc/esp32/system_internal.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/port/soc/esp32/system_internal.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/stack_check.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/stack_check.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/stack_check.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/startup.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/startup.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/startup.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/startup_funcs.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/startup_funcs.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/startup_funcs.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/system_time.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/system_time.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/system_time.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/task_wdt/task_wdt.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/task_wdt/task_wdt.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/task_wdt/task_wdt.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/task_wdt/task_wdt_impl_timergroup.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/task_wdt/task_wdt_impl_timergroup.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/task_wdt/task_wdt_impl_timergroup.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/ubsan.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/ubsan.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/ubsan.c.obj.d"
  "/Users/markgrun/esp/esp-idf/components/esp_system/xt_wdt.c" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/xt_wdt.c.obj" "gcc" "esp-idf/esp_system/CMakeFiles/__idf_esp_system.dir/xt_wdt.c.obj.d"
  )

# Targets to which this target links which contain Fortran sources.
set(CMAKE_Fortran_TARGET_LINKED_INFO_FILES
  )

# Targets to which this target links which contain Fortran sources.
set(CMAKE_Fortran_TARGET_FORWARD_LINKED_INFO_FILES
  )

# Fortran module output directory.
set(CMAKE_Fortran_TARGET_MODULE_DIR "")
