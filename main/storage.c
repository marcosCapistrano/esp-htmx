#include "storage.h"
#include "esp_spiffs.h"
#include "logger.h"

esp_err_t storage_init()
{
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/website",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = false
    };

    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            LOG_E("Failed to mount or format filesystem");
        }
        else if (ret == ESP_ERR_NOT_FOUND)
        {
            LOG_E("Failed to find SPIFFS partition");
        }
        else
        {
            LOG_E("Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return ESP_FAIL;
    }

    LOG_I("SPIFFS Initialized");

    return ESP_OK;
}