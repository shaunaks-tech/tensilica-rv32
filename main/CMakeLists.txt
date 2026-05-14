idf_component_register(
    SRCS
        "main.c"
        "rv32i.c"
        "memory.c"
    INCLUDE_DIRS "."
    REQUIRES
        log
        esp_timer
        esp_driver_uart
        freertos
)
