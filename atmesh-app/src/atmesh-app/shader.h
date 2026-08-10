#ifndef ATMESH_APP_SHADER_H_
#define ATMESH_APP_SHADER_H_

#include "atmesh-app/opengl.h"

GLuint compile_shader(GLenum type, const char* file_name);
GLuint link_program(GLuint vs, GLuint fs);

#endif // ATMESH_APP_SHADER_H_
