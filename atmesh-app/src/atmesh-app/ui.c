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

#include <stdlib.h>

typedef struct ui_s {
    struct nk_context* ctx;
    struct nk_glfw glfw;
} ui_t;

void ui_create(window_handle_t window, ui_handle_t* ui) {
    ui_t* internal = calloc(1, sizeof(ui_t));
    
    internal->ctx = nk_glfw3_init(&internal->glfw, (GLFWwindow*)window_get_native_handle(window), NK_GLFW3_INSTALL_CALLBACKS);

    struct nk_font_atlas* atlas;
    nk_glfw3_font_stash_begin(&internal->glfw, &atlas);
    nk_glfw3_font_stash_end(&internal->glfw);

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

    if (nk_begin(internal->ctx, "AtMesh", nk_rect(10, 10, 300, 200),
                 NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_TITLE)) {

        nk_layout_row_dynamic(internal->ctx, 30, 1);
        nk_label(internal->ctx, "Hello Nuklear!", NK_TEXT_LEFT);

        nk_layout_row_dynamic(internal->ctx, 30, 1);
        if (nk_button_label(internal->ctx, "Premi qui")) {
            // logica
        }
    }
    nk_end(internal->ctx);
}
