#include "atmesh-app/ui.h"
#include "atmesh-app/window.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

#include <nuklear.h>
#include <nuklear_glfw_gl3.h>

#include "ui_menu.h"
#include "ui_style.h"

#include <stdlib.h>

typedef struct ui_s {
    struct nk_context* ctx;
    struct nk_glfw glfw;
    GLFWwindow* window;
} ui_t;

void ui_create(window_handle_t window, ui_handle_t* ui) {
    ui_t* internal = calloc(1, sizeof(ui_t));
    
    internal->window = window_get_native_handle(window);
    internal->ctx = nk_glfw3_init(&internal->glfw, internal->window, NK_GLFW3_INSTALL_CALLBACKS);

    struct nk_font_atlas* atlas;
    nk_glfw3_font_stash_begin(&internal->glfw, &atlas);

    struct nk_font* font = nk_font_atlas_add_default(atlas, 23.0f, 0);

    nk_glfw3_font_stash_end(&internal->glfw);

    nk_style_set_font(internal->ctx, &font->handle);
    
    *ui = (ui_handle_t)internal;
}

void ui_destroy(ui_handle_t ui) {
    ui_t* internal = (ui_t*)ui;
    
    nk_glfw3_shutdown(&internal->glfw);
    free(internal);
}

void ui_begin_frame(ui_handle_t ui) {
    ui_t* internal = (ui_t*)ui;
    nk_glfw3_new_frame(&internal->glfw);
}

void ui_end_frame(ui_handle_t ui) {
    ui_t* internal = (ui_t*)ui;
    nk_glfw3_render(&internal->glfw, NK_ANTI_ALIASING_ON, 512 * 1024, 128 * 1024);
}

void ui_draw(ui_handle_t ui) {
    ui_t* internal = (ui_t*)ui;
    struct nk_context* ctx = internal->ctx;

    int fbw = 800, fbh = 600;
    glfwGetFramebufferSize(internal->window, &fbw, &fbh);

    ui_apply_style(ctx);
    
    if (nk_begin(ctx, "AtMeshMain", nk_rect(0, 0, (float)fbw, (float)fbh), NK_WINDOW_BACKGROUND)) {
        ui_menu_draw(ctx);
    }
    nk_end(ctx);
}
