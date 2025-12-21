#ifndef MCP_TEMPLATE_H
#define MCP_TEMPLATE_H

#include <stddef.h>

// Return codes for the callback
typedef enum {
    TPL_RET_OK, // Data found, continue processing
    TPL_RET_STOP // Data not found (end of loop) or error
} tpl_ret_t;

/**
 * The Data Provider Callback.
 * @param key       The variable name inside brackets (e.g., "name" or "contacts")
 * @param index     The current loop index (0 if not in a loop, 0,1,2... if inside {{#key}})
 * @param out_buf   Buffer to write the string result into
 * @param max_len   Maximum bytes to write
 * @param ctx       User context (optional, pass NULL if unused)
 */
typedef tpl_ret_t (*tpl_hook_t)(const char *key, int index, char *out_buf, size_t max_len, void *ctx);

/**
 * Renders the template.
 * @param tpl_str   The HTML template string
 * @param dest      The destination buffer for the final HTML
 * @param max_len   Size of destination buffer
 * @param hook      Your data provider function
 * @param ctx       Optional pointer to pass your data struct through
 */
void template_render(const char *tpl_str, char *dest, size_t max_len, tpl_hook_t hook, void *ctx);

#endif