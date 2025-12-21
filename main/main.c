#include "wifi.h"
#include "webserver.h"

void app_main(void)
{
    wifi_init();
    webserver_init();
}
