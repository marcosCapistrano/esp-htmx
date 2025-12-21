#ifndef MC_LOGGER_H
#define MC_LOGGER_H

#include "esp_log.h"

typedef enum
{
    LOG_LEVEL_NONE = 0,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_VERBOSE
} log_level_t;

void logger_set_level(log_level_t level);
log_level_t logger_get_level(void);

// MACROS BEGIN ----------------------------------------------

/* Helper macros to convert the integer __LINE__ into a string, for example "42" */
#define LOGGER_STR_HELPER(x) #x
#define LOGGER_STR(x) LOGGER_STR_HELPER(x)
/* ---------------------------------------------------------------------------------- */

#define LOG_E(format, ...)                                               \
    do                                                                   \
    {                                                                    \
        if (logger_get_level() >= LOG_LEVEL_ERROR)                       \
        {                                                                \
            ESP_LOGE(__FILE__ ":" LOGGER_STR(__LINE__), format, ##__VA_ARGS__); \
        }                                                                \
    } while (0)

#define LOG_W(format, ...)                                               \
    do                                                                   \
    {                                                                    \
        if (logger_get_level() >= LOG_LEVEL_WARN)                        \
        {                                                                \
            ESP_LOGW(__FILE__ ":" LOGGER_STR(__LINE__), format, ##__VA_ARGS__); \
        }                                                                \
    } while (0)

#define LOG_I(format, ...)                                               \
    do                                                                   \
    {                                                                    \
        if (logger_get_level() >= LOG_LEVEL_INFO)                        \
        {                                                                \
            ESP_LOGI(__FILE__ ":" LOGGER_STR(__LINE__), format, ##__VA_ARGS__); \
        }                                                                \
    } while (0)

#define LOG_D(format, ...)                                               \
    do                                                                   \
    {                                                                    \
        if (logger_get_level() >= LOG_LEVEL_DEBUG)                       \
        {                                                                \
            ESP_LOGD(__FILE__ ":" LOGGER_STR(__LINE__), format, ##__VA_ARGS__); \
        }                                                                \
    } while (0)

#define LOG_V(format, ...)                                               \
    do                                                                   \
    {                                                                    \
        if (logger_get_level() >= LOG_LEVEL_VERBOSE)                     \
        {                                                                \
            ESP_LOGV(__FILE__ ":" LOGGER_STR(__LINE__), format, ##__VA_ARGS__); \
        }                                                                \
    } while (0)

#define LOG_BUFFER_HEX(buffer, buff_len, level)                                                \
    do                                                                                         \
    {                                                                                          \
        if (logger_get_level() >= level)                                                       \
        {                                                                                      \
            esp_log_level_t esp_level;                                                         \
            switch (level)                                                                     \
            {                                                                                  \
            case LOG_LEVEL_ERROR:                                                              \
                esp_level = ESP_LOG_ERROR;                                                     \
                break;                                                                         \
            case LOG_LEVEL_WARN:                                                               \
                esp_level = ESP_LOG_WARN;                                                      \
                break;                                                                         \
            case LOG_LEVEL_INFO:                                                               \
                esp_level = ESP_LOG_INFO;                                                      \
                break;                                                                         \
            case LOG_LEVEL_DEBUG:                                                              \
                esp_level = ESP_LOG_DEBUG;                                                     \
                break;                                                                         \
            case LOG_LEVEL_VERBOSE:                                                            \
                esp_level = ESP_LOG_VERBOSE;                                                   \
                break;                                                                         \
            default:                                                                           \
                esp_level = ESP_LOG_INFO;                                                      \
                break;                                                                         \
            }                                                                                  \
            ESP_LOG_BUFFER_HEX_LEVEL(__FILE__ ":" LOGGER_STR(__LINE__), buffer, buff_len, esp_level); \
        }                                                                                      \
    } while (0)
// Section Header/Footer Macros
// Creates visually distinct sections in logs with ═══ borders

#define LOG_SECTION_WIDTH 50

#define _LOG_HEADER_IMPL(esp_log_fn, msg)                                      \
    do                                                                         \
    {                                                                          \
        int msg_len = strlen(msg);                                             \
        int padding = (LOG_SECTION_WIDTH - msg_len - 2) / 2;                   \
        if (padding < 2) padding = 2;                                          \
        char header[LOG_SECTION_WIDTH + 16];                                   \
        int pos = 0;                                                           \
        for (int i = 0; i < padding; i++) { header[pos++] = '='; }             \
        header[pos++] = ' ';                                                   \
        memcpy(&header[pos], msg, msg_len); pos += msg_len;                    \
        header[pos++] = ' ';                                                   \
        for (int i = 0; i < padding; i++) { header[pos++] = '='; }             \
        header[pos] = '\0';                                                    \
        esp_log_fn(__FILE__ ":" LOGGER_STR(__LINE__), "%s", header);           \
    } while (0)

#define _LOG_FOOTER_IMPL(esp_log_fn)                                           \
    do                                                                         \
    {                                                                          \
        char footer[LOG_SECTION_WIDTH + 1];                                    \
        for (int i = 0; i < LOG_SECTION_WIDTH; i++) { footer[i] = '='; }       \
        footer[LOG_SECTION_WIDTH] = '\0';                                      \
        esp_log_fn(__FILE__ ":" LOGGER_STR(__LINE__), "%s", footer);           \
    } while (0)

#define LOG_E_HEADER(msg)                                                      \
    do                                                                         \
    {                                                                          \
        if (logger_get_level() >= LOG_LEVEL_ERROR)                             \
            _LOG_HEADER_IMPL(ESP_LOGE, msg);                                   \
    } while (0)

#define LOG_E_FOOTER()                                                         \
    do                                                                         \
    {                                                                          \
        if (logger_get_level() >= LOG_LEVEL_ERROR)                             \
            _LOG_FOOTER_IMPL(ESP_LOGE);                                        \
    } while (0)

#define LOG_W_HEADER(msg)                                                      \
    do                                                                         \
    {                                                                          \
        if (logger_get_level() >= LOG_LEVEL_WARN)                              \
            _LOG_HEADER_IMPL(ESP_LOGW, msg);                                   \
    } while (0)

#define LOG_W_FOOTER()                                                         \
    do                                                                         \
    {                                                                          \
        if (logger_get_level() >= LOG_LEVEL_WARN)                              \
            _LOG_FOOTER_IMPL(ESP_LOGW);                                        \
    } while (0)

#define LOG_I_HEADER(msg)                                                      \
    do                                                                         \
    {                                                                          \
        if (logger_get_level() >= LOG_LEVEL_INFO)                              \
            _LOG_HEADER_IMPL(ESP_LOGI, msg);                                   \
    } while (0)

#define LOG_I_FOOTER()                                                         \
    do                                                                         \
    {                                                                          \
        if (logger_get_level() >= LOG_LEVEL_INFO)                              \
            _LOG_FOOTER_IMPL(ESP_LOGI);                                        \
    } while (0)

#define LOG_D_HEADER(msg)                                                      \
    do                                                                         \
    {                                                                          \
        if (logger_get_level() >= LOG_LEVEL_DEBUG)                             \
            _LOG_HEADER_IMPL(ESP_LOGD, msg);                                   \
    } while (0)

#define LOG_D_FOOTER()                                                         \
    do                                                                         \
    {                                                                          \
        if (logger_get_level() >= LOG_LEVEL_DEBUG)                             \
            _LOG_FOOTER_IMPL(ESP_LOGD);                                        \
    } while (0)

#define LOG_V_HEADER(msg)                                                      \
    do                                                                         \
    {                                                                          \
        if (logger_get_level() >= LOG_LEVEL_VERBOSE)                           \
            _LOG_HEADER_IMPL(ESP_LOGV, msg);                                   \
    } while (0)

#define LOG_V_FOOTER()                                                         \
    do                                                                         \
    {                                                                          \
        if (logger_get_level() >= LOG_LEVEL_VERBOSE)                           \
            _LOG_FOOTER_IMPL(ESP_LOGV);                                        \
    } while (0)

// MACROS END ----------------------------------------

#endif
