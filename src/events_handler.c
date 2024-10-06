#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
/*****PROJECT HEADERS*****/
#include "events_handler.h"
#include "global_vars.h"

bool event_loop() {
/* Main event loop that will handle keyboard events
 * that controls the sprite, catching events:
 *      - right key [ rotate 45 degrees right ]
 *      - left key [ rotate 45 degrees left ]
 *      - up key [ advance x num of pixels fwd ]
 *      - pen down
 *      - pen up
 * TODO:
 *      - implement funct to rotate sprite right
 *      - implement funct to rotate sprite left
 *      - implement funct to advance sprite x pixels fwd
 *      - implement funct to draw line as sprite advances
 *          [ pen down ]
 *      - implement funct to stop draw line as sprite advances
 *          [ pen up ]
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
                        break;
                    case SDLK_LEFT:
                        printf( "ROTATE 45 DEGREES LEFT\n" );
                        break;
                    case SDLK_UP:
                        printf( "ADVANCE FORWARD\n" );
                        break;
                    case SDLK_d:
                        printf( "PEN DOWN\n" );
                        break;
                    case SDLK_u:
                        printf( "PEN UP\n" );
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
            255,
            255,
            255,
            255
            );
    SDL_RenderClear( renderer );

/*  Uncommit once sprit logic added and rdy to test
 *  Make it it's own function
 *  
 *  SDL_SetRenderDrawColor(
 *      renderer,
 *      0,
 *      0,
 *      0,
 *      255
 *      );
 *  SDL_Rect sprite_rect = {
 *      sprite.x,
 *      sprite.y,
 *      50,  // Example sprite size
 *      50
 *      };
 */

    SDL_RenderPresent( renderer );    

    return true;
}

/********************************************************************/
// EVENT LOOP TEST CODE
SDL_Window* window;
SDL_Renderer* renderer;

#ifdef TEST_HANDLER
SDL_Window* window;

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
    
    // Start event loop
    while ( event_loop() ) {
        SDL_Delay( 10 );
    }

    return true;
}

void kill() {
    
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
}

int main( int argc, char* argv[] ) {   
   
    if ( !init() ) return 1;
    if ( !window_test_handler() ) return 1;
    
    printf( "SHUTTING DOWN\n" );
    kill();

    return 0;
}
#endif // TEST_HANDLER
