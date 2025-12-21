idf_component_register(
    SRCS "wifi.c"
    INCLUDE_DIRS "include"
    PRIV_REQUIRES logger esp_wifi nvs_flash 
)