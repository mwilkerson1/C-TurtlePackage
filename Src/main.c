#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#include "graphics.h"
#include "events.h"
#include "sprite.h"
#include "text.h"

#define WINDOW_TITLE "C-TurtlePackage: Interactive Turtle Graphics"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

// Global variables
SDL_Window* window = NULL;            // SDL window pointer
SDL_GLContext glContext;              // OpenGL context for rendering

int main(int argc, char* argv[]) {
    // Initialize window dimensions
    int windowWidth = WINDOW_WIDTH;
    int windowHeight = WINDOW_HEIGHT;

    // Initialize SDL and create window
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) > 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Request an OpenGL 2.1 context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // Request a compatibility profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    // Create SDL window with OpenGL support and resizable flag
    window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create OpenGL context for rendering in the window
    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        printf("Error creating OpenGL context: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! IMG_Error: %s\n", IMG_GetError());
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        IMG_Quit();
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize font
    if (!init_font("./Fonts/DejaVuSansMNerdFont-Regular.ttf", 12)) {
        TTF_Quit();
        IMG_Quit();
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize OpenGL
    setup_opengl(windowWidth, windowHeight);

    // Load sprite
    if (!load_sprite("./Images/mateo.png")) {
        close_font();
        TTF_Quit();
        IMG_Quit();
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize sprite properties
    sprite.x = windowWidth / 2.0f;
    sprite.y = windowHeight / 2.0f;
    sprite.angle = 0.0f;
    sprite.pen = false;
    sprite.r = 0.0f;
    sprite.g = 0.0f;
    sprite.b = 0.0f;

    // Main loop
    bool running = true;
    while (running) {
        // Calculate deltaTime
        static Uint32 lastTime = 0;
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f; // Convert milliseconds to seconds
        lastTime = currentTime;

        // Handle events
        running = handle_events(deltaTime, &windowWidth, &windowHeight);

        // Render scene
        render_scene(windowWidth, windowHeight);

        // Swap buffers to display the current frame
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    close_font();
    TTF_Quit();
    IMG_Quit();

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
