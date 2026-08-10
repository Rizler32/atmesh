#include "atmesh-app/window.h"
#include <GLFW/glfw3.h>

#include <atmesh/log.h>
#include <atmesh/assert.h>

#include <stdlib.h>

typedef struct window_s {
    GLFWwindow* handle;
} window_t;

bool window_create(window_handle_t* window, window_create_info_t* info) {
    // create internal window
    window_t* win = malloc(sizeof(window_t));
    ATMESH_ASSERT(win, "Out of memory for internal window");
    
    static bool glfw_inited = false;
    if (!glfw_inited) {
        glfw_inited = true;
        if (!glfwInit()) {
            ATMESH_ERROR("Failed to init GLFW");
            return false;
        }
    }

    // set OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window with size and pos
    GLFWwindow* internal = glfwCreateWindow(
        info->width, info->height,
        info->title,
        NULL, NULL
    );
    glfwSetWindowPos(internal, info->x, info->y);

    if (!internal) {
        ATMESH_ERROR("Failed to create internal window");
        return false;
    }

    // set output window fields
    win->handle = internal;
    *window = (window_handle_t)win;

    return true;
}

void window_destroy(window_handle_t window) {
    window_t* win = (window_t*)window;
    glfwDestroyWindow(win->handle);
}

void* window_get_native_handle(window_handle_t window) {
    window_t* win = (window_t*)window;
    return win ? win->handle : NULL;
}

bool window_should_close(window_handle_t window) {
    window_t* win = (window_t*)window;
    return glfwWindowShouldClose(win->handle);
}

void window_bind_opengl_context(window_handle_t window) {
    window_t* win = (window_t*)window;
    glfwMakeContextCurrent(win->handle);
}

void window_swap_buffers(window_handle_t window) {
    window_t* win = (window_t*)window;
    glfwSwapBuffers(win->handle);
}

void window_system_poll_events() {
    glfwPollEvents();
}

void window_system_shutdown() {
    glfwTerminate();
}
