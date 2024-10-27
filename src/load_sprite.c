#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>


extern SDL_Renderer* renderer;
extern SDL_Texture* imageTexture;

bool load_sprite( char* bmp ) {
    // Temp surface to load img into
    SDL_Surface *temp;

    // Load image
    temp = SDL_LoadBMP( bmp );

    // Check for errors
    if ( !temp ) {
        printf( "Error loading image: %s", SDL_GetError() );
        return false;
    }

    // Convert surface to texture
    imageTexture = SDL_CreateTextureFromSurface(
            renderer,
            temp
            );

    // Free temp surface
    SDL_FreeSurface( temp );
    
    // Check for errors
    if ( !imageTexture ) {
        printf( "Error converting surface: %s", SDL_GetError() );
    }

    return true;
}

