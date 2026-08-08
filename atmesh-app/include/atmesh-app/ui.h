#ifndef ATMESH_APP_UI_H_
#define ATMESH_APP_UI_H_

#include "gfx.h"

ATMESH_DECLARE_HANDLE(ui);

void ui_create(window_handle_t window, ui_handle_t* ui);
void ui_destroy(ui_handle_t ui);

void ui_begin_frame(ui_handle_t ui);
void ui_end_frame(ui_handle_t ui);
void ui_draw(ui_handle_t ui);

#endif // ATMESH_APP_UI_H_
