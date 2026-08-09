#include "ui_style.h"
// TODO update this shitty palette

#define C_BASE0 nk_rgb(0x0E, 0x0E, 0x0E)  /* sfondo principale */
#define C_BASE1 nk_rgb(0x14, 0x14, 0x14)  /* menubar, sidebar */
#define C_BASE2 nk_rgb(0x1F, 0x1F, 0x1F)  /* popup, hover */
#define C_BASE3 nk_rgb(0xC0, 0xC0, 0xC0)  /* testo, bordi */

#define C_ACCENT0 nk_rgb(0x7A, 0x7A, 0x7A) /* highlight discreto */

void ui_apply_style(struct nk_context* ctx) {
    struct nk_style* s = &ctx->style;

    /* --- MENUBAR --- */
    s->window.header.normal = nk_style_item_color(C_BASE1);
    s->window.header.hover  = nk_style_item_color(C_BASE2);
    s->window.header.active = nk_style_item_color(C_ACCENT0);

    s->window.header.padding = nk_vec2(6, 6);
    s->window.border = 0.0f;
    s->window.rounding = 0.0f;

    /* --- MENU BUTTON --- */
    s->menu_button.normal = nk_style_item_color(C_BASE1);
    s->menu_button.hover  = nk_style_item_color(C_BASE2);
    s->menu_button.active = nk_style_item_color(C_ACCENT0);

    s->menu_button.text_normal = C_BASE3;
    s->menu_button.text_hover  = C_ACCENT0;
    s->menu_button.text_active = C_ACCENT0;

    s->menu_button.padding = nk_vec2(4, 4);
    s->menu_button.border = 1.0f;
    s->menu_button.border_color = C_BASE3;
    s->menu_button.rounding = 4.0f;

    /* --- POPUP MENU --- */
    s->window.fixed_background = nk_style_item_color(C_BASE0);
    s->window.background = C_BASE0;
    s->window.border_color = C_BASE3;
    s->window.border = 1.0f;
    s->window.rounding = 0.0f;

    /* --- BUTTON (voci del popup) --- */
    s->button.normal = nk_style_item_color(C_BASE1);
    s->button.hover  = nk_style_item_color(C_BASE2);
    s->button.active = nk_style_item_color(C_ACCENT0);

    s->button.text_normal = C_BASE3;
    s->button.text_hover  = C_ACCENT0;
    s->button.text_active = C_ACCENT0;

    s->button.padding = nk_vec2(4, 4);
    s->button.border = 0.0f;
    s->button.rounding = 2.0f;

    /* --- SCROLLBAR --- */
    s->scrollh.normal = nk_style_item_color(C_BASE1);
    s->scrollh.hover  = nk_style_item_color(C_BASE2);
    s->scrollh.active = nk_style_item_color(C_ACCENT0);

    s->scrollh.cursor_normal = nk_style_item_color(C_BASE2);
    s->scrollh.cursor_hover  = nk_style_item_color(C_ACCENT0);
    s->scrollh.cursor_active = nk_style_item_color(C_ACCENT0);

    s->scrollv = s->scrollh;

    /* --- SLIDER --- */
    s->slider.bar_normal = C_BASE1;
    s->slider.bar_hover  = C_BASE2;
    s->slider.bar_active = C_ACCENT0;

    s->slider.cursor_normal = nk_style_item_color(C_BASE2);
    s->slider.cursor_hover  = nk_style_item_color(C_ACCENT0);
    s->slider.cursor_active = nk_style_item_color(C_ACCENT0);

    /* --- CHECKBOX --- */
    s->checkbox.normal = nk_style_item_color(C_BASE1);
    s->checkbox.hover  = nk_style_item_color(C_BASE2);
    s->checkbox.active = nk_style_item_color(C_ACCENT0);

    s->checkbox.text_normal = C_BASE3;
    s->checkbox.text_hover  = C_ACCENT0;
    s->checkbox.text_active = C_ACCENT0;

    /* --- SELECTABLE --- */
    s->selectable.normal = nk_style_item_color(C_BASE1);
    s->selectable.hover  = nk_style_item_color(C_BASE2);
    s->selectable.pressed = nk_style_item_color(C_ACCENT0);

    s->selectable.text_normal = C_BASE3;
    s->selectable.text_hover  = C_ACCENT0;
    s->selectable.text_pressed = C_ACCENT0;
}
