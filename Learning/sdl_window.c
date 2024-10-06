#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <wayland-client.h>

int main(int argc, char *argv[]) {
    SDL_Window* window = NULL;
    //SDL_SysWMinfo info;
    SDL_Surface* screenSurface = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a hidden SDL window
    window = SDL_CreateWindow(
            "Wayland Test Window", 
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640, 480,
            SDL_WINDOW_SHOWN
            );

    if (window == NULL) {
        printf(
            "SDL_CreateWindow Error: %s\n", SDL_GetError()
                );
        SDL_Quit();
        return 1;
    }
    else
    {
        //Get window surface
        screenSurface = SDL_GetWindowSurface( window );

        //Fill the surface white
        SDL_FillRect(
                screenSurface, 
                NULL, 
                SDL_MapRGB(
                    screenSurface->format, 0x00, 0x00, 0x00
                    ));
            
        //Update the surface
        SDL_UpdateWindowSurface( window );

        //Wait ten seconds
        SDL_Delay( 10000 );
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

