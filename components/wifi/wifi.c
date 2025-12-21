#include "wifi.h"
#include "logger.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "nvs.h"
#include <string.h>

#define WIFI_NVS_NAMESPACE "wifi_config"
#define WIFI_NVS_KEY_SSID "ssid"
#define WIFI_NVS_KEY_PASSWORD "password"

#define WIFI_DEFAULT_SSID CONFIG_WIFI_DEFAULT_SSID
#define WIFI_DEFAULT_PASSWORD CONFIG_WIFI_DEFAULT_PASSWORD
#define WIFI_CHANNEL 6
#define MAX_CONNECTIONS 4

static esp_err_t wifi_load_credentials(char *ssid, size_t ssid_len, char *password, size_t password_len)
{
    nvs_handle_t handle;
    esp_err_t ret = nvs_open(WIFI_NVS_NAMESPACE, NVS_READONLY, &handle);
    if (ret != ESP_OK) {
        return ret;
    }

    ret = nvs_get_str(handle, WIFI_NVS_KEY_SSID, ssid, &ssid_len);
    if (ret != ESP_OK) {
        nvs_close(handle);
        return ret;
    }

    ret = nvs_get_str(handle, WIFI_NVS_KEY_PASSWORD, password, &password_len);
    if (ret != ESP_OK) {
        nvs_close(handle);
        return ret;
    }

    nvs_close(handle);
    return ESP_OK;
}

esp_err_t wifi_save_credentials(const char *ssid, const char *password)
{
    nvs_handle_t handle;
    esp_err_t ret = nvs_open(WIFI_NVS_NAMESPACE, NVS_READWRITE, &handle);
    if (ret != ESP_OK) {
        LOG_E("Failed to open NVS namespace: %s", esp_err_to_name(ret));
        return ret;
    }

    ret = nvs_set_str(handle, WIFI_NVS_KEY_SSID, ssid);
    if (ret != ESP_OK) {
        LOG_E("Failed to save SSID: %s", esp_err_to_name(ret));
        nvs_close(handle);
        return ret;
    }

    ret = nvs_set_str(handle, WIFI_NVS_KEY_PASSWORD, password);
    if (ret != ESP_OK) {
        LOG_E("Failed to save password: %s", esp_err_to_name(ret));
        nvs_close(handle);
        return ret;
    }

    ret = nvs_commit(handle);
    if (ret != ESP_OK) {
        LOG_E("Failed to commit NVS: %s", esp_err_to_name(ret));
        nvs_close(handle);
        return ret;
    }

    nvs_close(handle);
    LOG_I("WiFi credentials saved to NVS");
    return ESP_OK;
}

esp_err_t wifi_init()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    if (ret != ESP_OK)
    {
        LOG_E("failed to init nvs");
        return ret;
    }

    ret = esp_netif_init();
    if (ret != ESP_OK)
    {
        LOG_E("failed to init netif");
        return ret;
    }

    ret = esp_event_loop_create_default();
    if (ret != ESP_OK)
    {
        LOG_E("failed to create event loop");
        return ret;
    }

    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ret = esp_wifi_init(&cfg);
    if (ret != ESP_OK)
    {
        LOG_E("failed to init wifi");
        return ret;
    }

    // Load credentials from NVS or use defaults
    char ssid[32] = {0};
    char password[64] = {0};
    if (wifi_load_credentials(ssid, sizeof(ssid), password, sizeof(password)) != ESP_OK) {
        strncpy(ssid, WIFI_DEFAULT_SSID, sizeof(ssid) - 1);
        strncpy(password, WIFI_DEFAULT_PASSWORD, sizeof(password) - 1);
        LOG_I("Using default WiFi credentials");
    } else {
        LOG_I("Loaded WiFi credentials from NVS");
    }

    wifi_config_t wifi_config = {
        .ap = {
            .channel = WIFI_CHANNEL,
            .max_connection = MAX_CONNECTIONS,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK,
        },
    };
    strncpy((char *)wifi_config.ap.ssid, ssid, sizeof(wifi_config.ap.ssid) - 1);
    wifi_config.ap.ssid_len = strlen(ssid);
    strncpy((char *)wifi_config.ap.password, password, sizeof(wifi_config.ap.password) - 1);

    ret = esp_wifi_set_mode(WIFI_MODE_AP);
    if (ret != ESP_OK)
    {
        LOG_E("failed to set wifi mode");
        return ret;
    }

    ret = esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config);
    if (ret != ESP_OK)
    {
        LOG_E("failed to set wifi config");
        return ret;
    }

    ret = esp_wifi_start();
    if (ret != ESP_OK)
    {
        LOG_E("failed to start wifi");
        return ret;
    }

    LOG_I_HEADER("WiFi AP initialized successfully");
    LOG_I("SSID: %s", ssid);
    LOG_I("Password: %s", password);
    LOG_D("Channel: %d", WIFI_CHANNEL);
    LOG_I_FOOTER();

    return ESP_OK;
}
