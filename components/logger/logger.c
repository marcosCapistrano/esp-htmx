#include "logger.h"

static log_level_t s_log_level = CONFIG_LOGGER_LEVEL;

void logger_set_level(log_level_t level)
{
    s_log_level = level;
}

log_level_t logger_get_level(void)
{
    return s_log_level;   
}
