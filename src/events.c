#include <stdio.h>
#include <SDL2/SDL.h>

typedef enum {
// Boolean enumeration
    false,
    true
} bool;

// Function prototypes
bool init();
void kill();
bool load();
bool loop();

// Pointers to window and surfaces
SDL_Window* window;
SDL_Surface* winSurface;
SDL_Surface* image1;
SDL_Surface* image2;

int main(int argc, char* argv[]) {
// main
    if ( !init() ) return 1;
    if ( !load() ) return 1;

    while ( loop () ) {
        SDL_Delay(10); // wait before processing the next frame
    }

    kill();

    return 0;
}

bool init() {
// Initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS ) > 0 ) {
        printf( "Error initializing SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
            "Example",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            SDL_WINDOW_SHOWN
            );
    if ( !window ) {
        printf( "Error creating window: %s", SDL_GetError());
        return false;
    }

    winSurface = SDL_GetWindowSurface( window );
    if ( !winSurface ) {
        printf( "Error getting surface: %s", SDL_GetError());
        return false;
    }

    return true;
}

void kill() {
// Fee allocated memory and quit SDL gracefully
    SDL_FreeSurface( image1 );
    SDL_FreeSurface( image2 );

    SDL_DestroyWindow( window );
    SDL_Quit();
}

bool load() {
// load bmp images and convert surfaces
    char* img1 = "/home/mateo/Projects/C_TurtlePackage/"
        "Images/blackbuck.bmp";
    char* img2 = "/home/mateo/Projects/C_TurtlePackage/"
        "Images/threecolors.bmp";

    SDL_Surface* temp1 = SDL_LoadBMP( img1 );
    SDL_Surface* temp2 = SDL_LoadBMP( img2 );
    if ( !temp1 || !temp2 ) {
        printf( "Error loading BMP: %s", SDL_GetError());
        return false;
    }

    image1 = SDL_ConvertSurface(
            temp1,
            winSurface->format,
            0
            );
    image2 = SDL_ConvertSurface(
            temp2,
            winSurface->format,
            0
            );
    if ( !image1 || !image2 ) {
        printf( "Error converting surface: %s", SDL_GetError());
        return false;
    }

    SDL_FreeSurface( temp1 );
    SDL_FreeSurface( temp2 );

    return true;
}

bool loop() {
// Event loop
    static bool renderImage2;
    SDL_Event e;

    // Blit image to entire window
    SDL_BlitScaled(
            image1,
            NULL,
            winSurface,
            NULL
            );

    while( SDL_PollEvent( &e ) != 0) {
        switch( e.type ) {
            case SDL_QUIT:
                return false;
            case SDL_KEYDOWN:
                // test keycode
                switch ( e.key.keysym.sym ) {
                    case SDLK_o:
                        renderImage2 = true;
                        break;
                    case SDLK_c:
                        renderImage2 = false;
                        break;
                };
            case SDL_MOUSEBUTTONDOWN:
                switch ( e.button.button ) {
                    case SDL_BUTTON_LEFT:
                        renderImage2 = true;
                        break;
                    case SDL_BUTTON_RIGHT:
                        renderImage2 = false;
                        break;
                }
        }
    }

    if ( renderImage2 ) {
        // Blit image to scaled portion of window
        SDL_Rect dest;
        dest.x = 160;
        dest.y = 120;
        dest.w = 320;
        dest.h = 240;
        SDL_BlitScaled(
                image2,
                NULL,
                winSurface,
                &dest
                );
    }

    // Update window
    SDL_UpdateWindowSurface( window );

    return true;
}
