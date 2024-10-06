#include <stdio.h>
#include <SDL2/SDL.h>

typedef enum {
    false, // 0
    true   // 1
} bool;

bool init();
void kill();
bool load(char* );

// PTRs to window and surfaces
SDL_Window* window;
SDL_Surface* winSurface;
SDL_Surface* image;

int main(int argc, char* argv[]) {
    //char* bmp = "/home/mateo/Projects/C_TurtlePackage/Images/"
    //    "blackbuck.bmp";
    char* bmp = "/home/mateo/Projects/C_TurtlePackage/Images/"
       "threecolors.bmp";
    
    
    if ( !init() ) return 1;
    if ( !load( bmp ) ) return 1;

    // Blit image to entire entire window
//    SDL_BlitSurface(
//            image,
//            NULL,
//            winSurface,
//            NULL
//            );

    // Blit image to scaled portion of window
    //SDL_Rect dest;
    //dest.x = 160;
    //dest.y = 120;
    //dest.w = 320;
    //dest.h = 240;
    SDL_BlitScaled(
            image,
            NULL,
            winSurface,
            NULL
            );

    // Update window
    SDL_UpdateWindowSurface( window );
    SDL_Delay(5000); // Wait for 5 seconds before closing
    
    kill();
    
    return 0;
}

bool load( char* bmp ) {
    // Temporary surfaces to load images into
    SDL_Surface *temp;
    
    // Load images
    temp = SDL_LoadBMP( bmp );
    // temp2 = SDL_LoadBMP( bmp );

    // Check for errors
    if ( !temp ) {
        printf( "Error loading image: %s", SDL_GetError() );
        return false;
    }

    // Format surfaces
    image = SDL_ConvertSurface(
            temp,
            winSurface->format,
            0
            );
    
    // Free temp surfaces
    SDL_FreeSurface( temp );
    
    // Check for errors
    if ( !image ) {
        printf( "Error converting surface: %s", SDL_GetError() );
    }
    
    return true;
}

bool init() {
    // Initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "Error initializing SDL: %s", SDL_GetError() );
        return false;
    }

    // Create a window
    window = SDL_CreateWindow(
            "Example",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800,
            800,
            SDL_WINDOW_SHOWN
            );
    
    // Get surface
    winSurface = SDL_GetWindowSurface( window );
    // Check for errors
    if ( !winSurface ) {
        printf( "Error getting surface: %s", SDL_GetError() );
        return false;
    }

    return true;
}

void kill() {
    // Free images
    SDL_FreeSurface( image );
    
    // Quit
    SDL_DestroyWindow( window );
    SDL_Quit();
}

