idf_component_register(SRCS "storage.c" "main.c" "webserver.c"
                       REQUIRES wifi logger template
                       PRIV_REQUIRES spi_flash esp_http_server spiffs
                       INCLUDE_DIRS "")
