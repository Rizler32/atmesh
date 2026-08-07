#include "atmesh-app/opengl.h"
#include <GLFW/glfw3.h>

#include <atmesh/log.h>

bool opengl_init() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        ATMESH_ERROR("Failed to initialize GLAD");
        return 1;
    }
}
