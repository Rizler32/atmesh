#include "shader.h"
#include <atmesh/log.h>
#include <stdlib.h>
#include <stdio.h>

static inline bool _read_file(const char* file_name, char** out_data) {
    FILE* file = fopen(file_name, "rb");
    if (!file) {
        *out_data = NULL;
        return false;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = malloc(size + 1);
    if (!buffer) {
        fclose(file);
        *out_data = NULL;
        return false;
    }

    size_t read = fread(buffer, 1, size, file);
    fclose(file);

    buffer[read] = '\0';

    *out_data = buffer;
    return true;
}

GLuint compile_shader(GLenum type, const char* file_name) {
    char* src = NULL;

    if (!_read_file(file_name, &src)) {
        ATMESH_ERROR("Failed to read shader file: %s", file_name);
        return 0;
    }

    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, (const char* const*)&src, NULL);
    glCompileShader(s);

    free(src);

    GLint ok = 0;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetShaderInfoLog(s, sizeof(log), NULL, log);
        ATMESH_ERROR("Shader compile error (%s): %s", file_name, log);
        glDeleteShader(s);
        return 0;
    }

    return s;
}

GLuint link_program(GLuint vs, GLuint fs) {
    GLuint p = glCreateProgram();
    glAttachShader(p, vs);
    glAttachShader(p, fs);

    glBindAttribLocation(p, 0, "in_pos");
    glBindAttribLocation(p, 1, "in_norm");

    glLinkProgram(p);

    GLint ok = 0;
    glGetProgramiv(p, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetProgramInfoLog(p, sizeof(log), NULL, log);
        ATMESH_ERROR("Program link error: %s", log);
        glDeleteProgram(p);
        return 0;
    }

    return p;
}
