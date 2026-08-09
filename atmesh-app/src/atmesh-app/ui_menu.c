#include "atmesh-app/ui_menu.h"
#include "events.h"

void ui_menu_draw(struct nk_context* ctx) {
    const int row_height = 32;
    const int item_width = 98;
    const struct nk_vec2 menu_label_size = nk_vec2(200, 200);

    nk_menubar_begin(ctx);
    nk_layout_row_static(ctx, row_height, item_width, 3);

    /* --- MENU FILE --- */
    if (nk_menu_begin_label(ctx, "File", NK_TEXT_CENTERED, menu_label_size)) {
        nk_layout_row_dynamic(ctx, row_height, 1);

        if (nk_button_label(ctx, "Open...")) { on_file_open(); }
        if (nk_button_label(ctx, "Save")) { on_file_save(); }

        nk_menu_end(ctx);
    }

    /* --- MENU EDIT --- */
    if (nk_menu_begin_label(ctx, "Edit", NK_TEXT_CENTERED, menu_label_size)) {
        nk_layout_row_dynamic(ctx, row_height, 1);

        if (nk_button_label(ctx, "Undo")) {}
        if (nk_button_label(ctx, "Redo")) {}
        if (nk_button_label(ctx, "Preferences")) {}

        nk_menu_end(ctx);
    }

    /* --- MENU HELP --- */
    if (nk_menu_begin_label(ctx, "Help", NK_TEXT_CENTERED, menu_label_size)) {
        nk_layout_row_dynamic(ctx, row_height, 1);

        if (nk_button_label(ctx, "Documentation")) {}
        if (nk_button_label(ctx, "About")) {}

        nk_menu_end(ctx);
    }

    nk_menubar_end(ctx);
}
