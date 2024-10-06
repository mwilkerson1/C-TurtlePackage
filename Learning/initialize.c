#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    printf("Initializing SDL.\n");

    // Initialize defaults, video and audio
    if ((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1))
    {
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(-1);
    }

    printf("SDL initialized.\n");

    // Create a window
    SDL_Window* window = SDL_CreateWindow(
            "my window",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            640,
            480,
            SDL_WINDOW_SHOWN
            );

    // Check for errors - returns NULL ptr
    if (!window)
    {
        printf(
            "Failed to create a window! Error: %s", SDL_GetError()
            );
    }
    
    // Get the surface from the window
    SDL_Surface* windowSurface = SDL_GetWindowSurface(window);

    // Fill the window with a white rectangle
    SDL_FillRect(
            windowSurface,
            NULL,
            SDL_MapRGB(
                windowSurface->format,
                255,
                255,
                255
                ));
    
    // Update the window display
    SDL_UpdateWindowSurface(window);
    
    // Wait
    char c = '\0';
    while (!c)
    {
        getchar();
    }
    
    // Destroy the window and its surface
    SDL_DestroyWindow(window);
    window = NULL;
    windowSurface = NULL;

    printf("Quiting SDL.\n");

    // Quit SDL
    SDL_Quit();

    printf("Quiting...\n");

    return 0;
}
