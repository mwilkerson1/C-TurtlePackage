#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL_ttf.h>

#include "sprite.h"
#include "utilities.h"

// Function prototypes
void setup_opengl(int windowWidth, int windowHeight);
bool load_sprite(const char* bmp);
void render_scene(int windowWidth, int windowHeight);
GLuint render_text(const char* text, SDL_Color color, int* w, int* h);

#endif // GRAPHICS_H
