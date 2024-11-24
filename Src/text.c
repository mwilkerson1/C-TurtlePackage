#include "text.h"
#include "utilities.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>  
#include <stdbool.h>  
#include <stdio.h>

static TTF_Font* font = NULL;

bool init_font(const char* fontPath, int fontSize) {
    font = TTF_OpenFont(fontPath, fontSize);
    if (!font) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        return false;
    }
    return true; 
}

void close_font() {
    if (font) {
        TTF_CloseFont(font);
        font = NULL;
    }
}

GLuint render_text(const char* text, SDL_Color color, int* w, int* h) {
    // Render text to a surface
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, color);
    if (!textSurface) {
        printf("Unable to render text surface! TTF_Error: %s\n", TTF_GetError());
        return 0;
    }

    // Convert the surface to a format suitable for OpenGL texture
    SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(textSurface, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(textSurface);

    if (!formattedSurface) {
        printf("Error converting text surface: %s\n", SDL_GetError());
        return 0;
    }

    // Generate a texture ID
    GLuint textureID;
    glGenTextures(1, &textureID);

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set pixel storage mode
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Set alignment to 1 for tight packing

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, formattedSurface->w, formattedSurface->h, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, formattedSurface->pixels);

    // Check for OpenGL errors
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        printf("OpenGL error after glTexImage2D: %s\n", gluErrorString(err));
    }

    // Set the width and height
    *w = formattedSurface->w;
    *h = formattedSurface->h;

    // Free the surface
    SDL_FreeSurface(formattedSurface);

    return textureID;
}
