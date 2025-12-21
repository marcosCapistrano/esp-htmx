#include "template.h"
#include <string.h>
#include <stdio.h>

// Internal recursive function
static const char* process(const char *cursor, const char *end, char **out_ptr, const char *out_end, tpl_hook_t hook, int index, void *ctx) {
    while (cursor < end && *out_ptr < out_end) {
        
        // 1. Detect Start Tag "{{"
        if (cursor[0] == '{' && cursor[1] == '{') {
            const char *tag_start = cursor + 2;
            const char *tag_end = strstr(tag_start, "}}");
            if (!tag_end) break; // Error: No closing bracket

            // Extract Key
            char key[32];
            size_t klen = tag_end - tag_start;
            if (klen > 31) klen = 31;
            strncpy(key, tag_start, klen);
            key[klen] = '\0';

            // 2. Handle Block/Loop: "{{#key}}"
            if (key[0] == '#') {
                const char *clean_key = key + 1;
                
                // Find matching closing tag "{{/key}}"
                char close_tag[36];
                snprintf(close_tag, sizeof(close_tag), "{{/%s}}", clean_key);
                const char *block_end = strstr(tag_end, close_tag);

                if (block_end) {
                    // Loop Logic: Ask provider for index 0, 1, 2... until TPL_RET_STOP
                    int loop_idx = 0;
                    char check_buf[2]; // Dummy buffer to check existence
                    
                    while (hook(clean_key, loop_idx, check_buf, 0, ctx) == TPL_RET_OK) {
                        // Recursively render the block content
                        // Note: We pass the start of content (tag_end + 2) and end of content (block_end)
                        process(tag_end + 2, block_end, out_ptr, out_end, hook, loop_idx, ctx);
                        loop_idx++;
                        
                        // Safety check: prevent buffer overflow inside loop
                        if (*out_ptr >= out_end) break;
                    }
                    
                    cursor = block_end + strlen(close_tag); // Skip past the whole block
                    continue;
                }
            }
            
            // 3. Handle Variable: "{{key}}"
            else {
                // Ask the hook for the value
                // We use the current recursion 'index' (0 if top level, N if inside loop)
                size_t space = out_end - *out_ptr;
                if (hook(key, index, *out_ptr, space, ctx) == TPL_RET_OK) {
                    *out_ptr += strlen(*out_ptr); // Advance pointer by written amount
                }
                cursor = tag_end + 2;
                continue;
            }
        }

        // 4. Regular Character Copy
        **out_ptr = *cursor;
        (*out_ptr)++;
        cursor++;
    }
    **out_ptr = '\0'; // Null terminate
    return cursor;
}

void template_render(const char *tpl_str, char *dest, size_t max_len, tpl_hook_t hook, void *ctx) {
    char *out_ptr = dest;
    process(tpl_str, tpl_str + strlen(tpl_str), &out_ptr, dest + max_len - 1, hook, 0, ctx);
}