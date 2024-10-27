#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
/*****PROJECT HEADERS*****/
#include "events_handler.h"
#include "global_vars.h"
#include "sprite_logic.h"
#include "load_sprite.h"

#ifdef TEST_HANDLER
SDL_Window*   window;
SDL_Renderer* renderer;
SDL_Texture*  imageTexture;
SDL_Rect      destRect;
Sprite        sprite;


// Set sprite start position and orientation
#define X_START   400
#define Y_START   400
#define PEN_START false
#define IMG       "/home/mateo/Projects/C_TurtlePackage/Images/blackbuck.bmp"
#define IMG_W     50
#define IMG_H     50 
#endif

bool event_loop() {
/* Main event loop that will handle keyboard events
 * that controls the sprite, catching events:
 *      - right key [ rotate 45 degrees right ]
 *      - left key [ rotate 45 degrees left ]
 *      - up key [ advance x num of pixels fwd ]
 *      - pen down
 *      - pen up
 * It calls functions from sprite_logic.h that will
 * update the sprite structure's members based on 
 * keyboard events.
 */
    SDL_Event evt;
    
    while( SDL_PollEvent ( &evt ) != 0 ) {
        switch( evt.type ) {
            case SDL_QUIT: 
                return false;
            case SDL_KEYDOWN:
                switch ( evt.key.keysym.sym ) {
                    case SDLK_RIGHT:
                        printf( "ROTATE 45 DEGREES RIGHT\n" );
                        update_orientation( TURN_RIGHT );
                        printf( "angle: %d\n", sprite.angle );
                        break;
                    case SDLK_LEFT:
                        printf( "ROTATE 45 DEGREES LEFT\n" );
                        update_orientation( TURN_LEFT );
                        printf( "angle: %d\n", sprite.angle );
                        break;
                    case SDLK_UP:
                        printf( "ADVANCE FORWARD\n" );
                        update_location( );
                        printf( "loc: ( %d, %d )\n", sprite.x, sprite.y );
                        break;
                    case SDLK_d:
                        printf( "PEN DOWN\n" );
                        update_pen( true );
                        printf( "pen: %d\n", sprite.pen );
                        break;
                    case SDLK_u:
                        printf( "PEN UP\n" );
                        update_pen( false );
                        printf( "pen: %d\n", sprite.pen );
                        break;
                    case SDLK_ESCAPE:
                        return false;
                }
            case SDL_MOUSEMOTION: // Catching mouse motion to prevent
                continue;         // screen from turning black when
        }                         // mouse moves
    }    
    
    SDL_SetRenderDrawColor(
            renderer,
            100,
            255,
            50,
            255
            );
    SDL_RenderClear( renderer );

    destRect.x = sprite.x;
    destRect.y = sprite.y;
    destRect.w = IMG_W;
    destRect.h = IMG_H;

    SDL_Point center = {
        destRect.w / 2,
        destRect.h / 2
    };

    SDL_RenderCopyEx(
            renderer,
            imageTexture,
            NULL,
            &destRect,
            sprite.angle,
            &center,
            SDL_FLIP_HORIZONTAL
            );

    SDL_RenderPresent( renderer );    

    return true;
}

/********************************************************************/
// EVENT LOOP TEST CODE
#ifdef TEST_HANDLER
bool init() {
    
    if ( SDL_Init ( SDL_INIT_VIDEO | SDL_INIT_EVENTS ) > 0 ) {
        printf( "Error initializing SDL: %s\n", SDL_GetError() );
        return false;
    }

    return true;
}

bool window_test_handler() {
   
    window = SDL_CreateWindow(
            "Dummy",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            800,
            800,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
            );
    if ( !window ) {
        printf( "Error creating a dummy window\n" );
        return false;
    }

    renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED
            );

    if ( !renderer ) {
        printf( "Error creating renderer: %s", SDL_GetError() );
        return false;
    }

    if ( !load_sprite( IMG ) ) return false; 
    
    // Start event loop
    while ( event_loop() ) {
        SDL_Delay( 10 );
    }

    return true;
}

void kill() {
    SDL_DestroyTexture( imageTexture );
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
}

int main( int argc, char* argv[] ) {   

    sprite.x = X_START;
    sprite.y = Y_START;
    sprite.pen = PEN_START;

    if ( !init() ) return 1;
    if ( !window_test_handler() ) return 1;
    
    printf( "SHUTTING DOWN\n" );
    kill();

    return 0;
}
#endif // TEST_HANDLER
