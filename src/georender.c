#include <stdio.h>
#include <SDL2/SDL.h>

typedef enum {
    false,
    true
} bool;

bool init();
void kill();
bool loop();

SDL_Window* window;
SDL_Renderer* renderer;
const unsigned char* keys;

int main(int argc, char* argv[]) {
    if ( !init() ) return 1;

    while ( loop() ) {
        SDL_Delay(10);
    }

    return 0;
}

bool init() {
    if ( SDL_Init ( SDL_INIT_VIDEO | SDL_INIT_EVENTS) > 0 ) {
        printf( "SDL failed to initialize: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
            "Example",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            800,
            800,
            SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI );
    if ( !window ) {
        printf( "Error creating window: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer( 
            window,
            -1,
            SDL_RENDERER_ACCELERATED
            );
    if ( !renderer ) {
        printf( "Error creating renderer: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(
            renderer,
            255,
            255,
            255,
            255
            );
    SDL_RenderClear( renderer );
    SDL_RenderPresent( renderer );

    keys = SDL_GetKeyboardState( NULL );

    return true;
}

void kill() {
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
}

bool loop() {
    SDL_Event e;
   // SDL_Rect r;
    static int mx0 = -1, my0 = -1, mx1 = -1, my1 = -1;

    SDL_SetRenderDrawColor( 
            renderer,
            255,
            255,
            255,
            255
            );
    SDL_RenderClear( renderer );

    while ( SDL_PollEvent( &e ) != 0 ) {
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        switch ( e.type ) {
            case SDL_QUIT:
                return false;
            case SDL_MOUSEBUTTONDOWN:
                mx0 = e.button.x;
                my0 = e.button.y;
                while ( e.type != SDL_MOUSEBUTTONUP ) { 
                    SDL_RenderDrawPoint( renderer, mx0, my0 );
                    SDL_RenderPresent( renderer );
                    SDL_PollEvent( &e );
                    mx0 = e.button.x;
                    my0 = e.button.y;
                }
               /*
                break;
            case SDL_MOUSEMOTION:
                mx1 = e.button.x;
                my1 = e.button.y;
                //SDL_RenderDrawPoint( renderer, mx1, my1 );
                break; */
            case SDL_MOUSEBUTTONUP:
                mx0 = my0 = mx1 = my1 = -1;
                break;
        }
    }
/*
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

    if ( keys[SDL_SCANCODE_1] ) {
        SDL_RenderDrawPoint(
                renderer,
                10,
                10
                );
    }
    if ( keys[SDL_SCANCODE_2] ) {
        SDL_RenderDrawLine(
                renderer,
                10,
                20,
                10,
                100
                );
    }
    if ( keys[SDL_SCANCODE_3] ) {
        r.x = 20;
        r.y = 20;
        r.w = 100;
        r.h = 100;
        SDL_RenderFillRect( renderer, &r );
    }
    if ( mx0 != -1 ) {
        r.x = mx0;
        r.y = my0;
        //r.w = mx1 - mx0;
        //r.h = my1 - my0;
        SDL_RenderDrawPoint( renderer, mx0, my0 );
    }
*/
    SDL_RenderPresent( renderer );

    return true;
}
