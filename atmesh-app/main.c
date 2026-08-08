#include "atmesh-app/window.h"
#include "atmesh-app/opengl.h"
#include "atmesh-app/ui.h"

#include <atmesh/log.h>
#include <atil/platform/platform.h>

int main() {
    ATMESH_INFO("Launching AtMesh");
    
    // create window
    ATMESH_INFO("Creating window");

    window_create_info_t window_info = {
        .width = 1600,
        .height = 1200,
        .title = "AtMesh"
    };

    window_handle_t window;
    if (!window_create(&window, &window_info)) {
        ATMESH_ERROR("Failed to create window");
        return 1;
    }

    // bind opengl context and init
    window_bind_opengl_context(window);

    ATMESH_INFO("Window created successfully");

    opengl_init();
    glClearColor(0,0,0,0);
    ATMESH_INFO("Initialized OpenGL");

    // create ui
    ui_handle_t ui;
    ui_create(window, &ui);

    while (!window_should_close(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        ui_begin_frame(ui);
        ui_draw(ui);
        ui_end_frame(ui);
        
        window_swap_buffers(window);
        window_system_poll_events();

        atil_platform_sleep_ms(16);
    }

    // shutdown
    ATMESH_INFO("Destroying ui");
    ui_destroy(ui);
    
    ATMESH_INFO("Destroying window");
    window_destroy(window);
    window_system_shutdown();

    ATMESH_INFO("AtMesh exited successfully");
    return 0;
}
