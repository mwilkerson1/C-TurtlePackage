#include "utilities.h"
#include <stdio.h>
#include <GL/glu.h>

void checkOpenGLError(const char* stmt) {
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        printf("OpenGL error %08x, at %s\n", err, stmt);
    }
}
