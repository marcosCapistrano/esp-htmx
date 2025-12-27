#include "wifi.h"
#include "storage.h"
#include "webserver.h"

void app_main(void)
{
    wifi_init();
    storage_init();
    webserver_init();
}
