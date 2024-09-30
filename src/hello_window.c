#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! \
                SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Set OpenGL version and profile
    SDL_GL_SetAttribute(
            SDL_GL_CONTEXT_MAJOR_VERSION, 3
            );
    SDL_GL_SetAttribute(
            SDL_GL_CONTEXT_MINOR_VERSION, 3
            );
    SDL_GL_SetAttribute(
            SDL_GL_CONTEXT_PROFILE_MASK, 
            SDL_GL_CONTEXT_PROFILE_CORE
            );

    // Create SDL Window with OpenGL context
    SDL_Window* window = SDL_CreateWindow(
            "SDL OpenGL Window",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800, 600,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
            );

    if (window == NULL) {
        printf("Window could not be created! \
                SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Create OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (glContext == NULL) {
        printf("OpenGL context could not be created! \
                SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Main loop 
    SDL_Delay(3000);  // Wait for 3 seconds before closing

    // Clean up
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}

