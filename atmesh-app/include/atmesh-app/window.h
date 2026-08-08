#ifndef ATMESH_APP_WINDOW_H_
#define ATMESH_APP_WINDOW_H_

#include "gfx.h"
#include <stdbool.h>

typedef struct window_create_info_s {
    int width;
    int height;
    const char* title;
} window_create_info_t;

bool window_create(window_handle_t* window, window_create_info_t* info);
void window_destroy(window_handle_t window);

void* window_get_native_handle(window_handle_t window);

bool window_should_close(window_handle_t window);
void window_bind_opengl_context(window_handle_t window);

void window_swap_buffers(window_handle_t window);

void window_system_poll_events();
void window_system_shutdown();

#endif // ATMESH_APP_WINDOW_H_
