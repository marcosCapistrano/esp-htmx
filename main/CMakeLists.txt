idf_component_register(SRCS "main.c" "webserver.c"
                       REQUIRES wifi logger template
                       PRIV_REQUIRES spi_flash esp_http_server
                       INCLUDE_DIRS "")
