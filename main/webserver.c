#include "esp_http_server.h"
#include "logger.h"
#include "template.h"

#define QUERY_MAX_BUFFER_LEN 256
#define HTTPD_301 "301 Moved Permanently"

typedef struct
{
    const char search[128];
} page_data_t;

tpl_ret_t contacts_hook(const char *key, int index, char *out, size_t max, void *ctx)
{
    page_data_t *data = (page_data_t *)ctx;
    LOG_E("key: %s", key);
    if (strcmp(key, "search") == 0)
    {
        snprintf(out, max, "%s", data->search);
        return TPL_RET_OK;
    }

    return TPL_RET_STOP; // Key not found
}

static esp_err_t contacts_handler(httpd_req_t *req)
{
    char search_param[128] = {0}; // holds the parameter for the contact name, or empty if none

    char query_buf[QUERY_MAX_BUFFER_LEN] = {0};
    size_t query_buf_len = 0;

    query_buf_len = httpd_req_get_url_query_len(req) + 1;

    if (query_buf_len > 1 && query_buf_len < QUERY_MAX_BUFFER_LEN)
    {
        if (httpd_req_get_url_query_str(req, query_buf, query_buf_len) == ESP_OK)
        {
            httpd_query_key_value(query_buf, "q", search_param, sizeof(search_param));
        }
    }

    const char *index_html =
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "    <title>Document</title>\n"
        "</head>\n"
        "\n"
        "<body>\n"
        "    <form action=\"/contacts\" method=\"get\" class=\"tool-bar\">\n"
        "    <label for=\"search\">Search Term</label>\n"
        "    <input id=\"search\" type=\"search\" name=\"q\"\n"
        "      value=\"{{search}}\" />\n"
        "    <input type=\"submit\" value=\"Search\"/>\n"
        "  </form>\n"
        "</body>\n"
        "\n"
        "</html>";

    char buffer[512] = {0};

    page_data_t page_data = {0};
    strcpy(page_data.search, search_param);

    template_render(index_html, buffer, sizeof(buffer), contacts_hook, &page_data);

    httpd_resp_send(req, buffer, strlen(buffer));

    return ESP_OK;
}

httpd_uri_t contacts_uri = {
    .uri = "/contacts",
    .method = HTTP_GET,
    .handler = contacts_handler,
};

static esp_err_t index_handler(httpd_req_t *req)
{
    httpd_resp_set_status(req, HTTPD_301);
    httpd_resp_set_hdr(req, "Location", "/contacts");

    httpd_resp_send(req, NULL, 0);

    return ESP_OK;
}

httpd_uri_t index_uri = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = index_handler,
};

static httpd_handle_t s_server;

esp_err_t webserver_init()
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    if (httpd_start(&s_server, &config) != ESP_OK)
    {
        LOG_E("failed to start webserver");
        return ESP_FAIL;
    }

    // register uri handlers
    httpd_register_uri_handler(s_server, &contacts_uri);
    httpd_register_uri_handler(s_server, &index_uri);

    LOG_I("Webserver initialized");
    return ESP_OK;
}