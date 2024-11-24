#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL_ttf.h>
#include <GL/gl.h>
#include <stdbool.h>  // Add this line

// Function prototypes
bool init_font(const char* fontPath, int fontSize);
void close_font();
GLuint render_text(const char* text, SDL_Color color, int* w, int* h);

#endif // TEXT_H
