
/**********LIBRARIES**********/
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>


/**********MACROS**********/
#define X_START 400
#define Y_START 400
#define MOVE_DISTANCE 20
#define PEN_START false
#define IMG "/home/milkiwilki/Documents/School/csc451/C-TurtlePackage/Images/blackbuck.bmp"
#define IMG_W 50
#define IMG_H 50


/***********STRUCTS & ENUMS**********/
typedef enum {
    TURN_LEFT = 0,
    TURN_RIGHT = 1
} TurnDirection;

typedef struct {
    int x;
    int y;
    int angle;
    TurnDirection turn;
    bool pen;
} Sprite;


/**********FUNCTION PROTOTYPES**********/
bool init();
bool window_test_handler();
void kill();
bool event_loop();
bool load_sprite(char* bmp);
void update_location();
void update_orientation(TurnDirection direction);
void update_pen(bool pen_state);
void draw_line(int x1, int y1, int x2, int y2);


/**********GLOBAL VARIABLES**********/
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* imageTexture;
SDL_Texture* lineTexture;
SDL_Rect destRect;
Sprite sprite;


/**********MAIN**********/
int main(int argc, char* argv[]) {
    sprite.x = X_START;
    sprite.y = Y_START;
    sprite.pen = PEN_START;

    if (!init()) return 1;
    if (!window_test_handler()) return 1;

    printf("SHUTTING DOWN\n");
    kill();

    return 0;
}


/**********FUNCTIONS**********/
bool init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) > 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return false;
    }

    return true;
}


bool window_test_handler() {
    window = SDL_CreateWindow(
    	"Interactive Turtle Graphics", 
    	SDL_WINDOWPOS_UNDEFINED, 
    	SDL_WINDOWPOS_UNDEFINED, 
    	800, 
    	800, 
    	SDL_WINDOW_SHOWN
    	);

    if (!window) {
        printf("Error creating window: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(
    	window, -1, 
    	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    	);

    if (!renderer) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        return false;
    }

    if (!load_sprite(IMG)) return false;

    // Create a texture for persistent lines, matching the window size
    lineTexture = SDL_CreateTexture(
    	renderer, 
    	SDL_PIXELFORMAT_RGBA8888, 
    	SDL_TEXTUREACCESS_TARGET, 
    	800, 
    	800
    	);

    SDL_SetRenderTarget(renderer, lineTexture);
    SDL_SetRenderDrawColor(renderer, 100, 255, 50, 255); // Background color
    SDL_RenderClear(renderer); // Clear the texture with the background color
    SDL_SetRenderTarget(renderer, NULL); // Reset render target to default

    // Run event loop
    while (event_loop()) {
        SDL_Delay(10);
    }

    return true;
}

void kill() {
    SDL_DestroyTexture(imageTexture);
    SDL_DestroyTexture(lineTexture); // Free the line texture
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


bool event_loop() {
    SDL_Event evt;
    static int previous_x = X_START;
    static int previous_y = Y_START;

    while (SDL_PollEvent(&evt) != 0) {
        
        switch (evt.type) {

            case SDL_QUIT:
                return false;
            case SDL_KEYDOWN:
                switch (evt.key.keysym.sym) {

                    case SDLK_RIGHT:
                        printf( "ROTATE 45 DEGREES RIGHT\n" );
                        update_orientation(TURN_RIGHT);
                        break;
                    case SDLK_LEFT:
                        printf( "ROTATE 45 DEGREES LEFT\n" );
                        update_orientation(TURN_LEFT);
                        break;
                    case SDLK_UP:
                        printf( "ADVANCE FORWARD\n" );
                        previous_x = sprite.x;
                        previous_y = sprite.y;
                        update_location();

                        if (sprite.pen) {
                            draw_line(
                            	previous_x, 
                            	previous_y, 
                            	sprite.x, 
                            	sprite.y
                            	);
                        }

                        break;
                    case SDLK_d:
                        printf( "PEN DOWN\n" );
                        update_pen(true);
                        break;
                    case SDLK_u:
                        printf( "PEN UP\n" );
                        update_pen(false);
                        break;
                    case SDLK_ESCAPE:
                        return false;
                }
                break;
        }
    }

    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 100, 255, 50, 255);
    SDL_RenderClear(renderer);

    // Render the line texture (persistent lines)
    SDL_RenderCopy(renderer, lineTexture, NULL, NULL);

    // Draw the sprite (texture)
    destRect.x = sprite.x;
    destRect.y = sprite.y;
    destRect.w = IMG_W;
    destRect.h = IMG_H;
    SDL_Point center = { destRect.w / 2, destRect.h / 2 };
    SDL_RenderCopyEx(renderer, imageTexture, NULL, &destRect, sprite.angle, &center, SDL_FLIP_NONE);

    SDL_RenderPresent(renderer);

    return true;
}


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


void update_location() {
/* update_location computes the new coordinates of 
 * sprite based on its orientation and fwd advancement;
 * it uses the following formulas:
 *      x_2 = x_1 + d * cos( sprite.angle * ( pi/180 ))
 *      y_2 = y_1 + d * sin( sprite.angle * ( pi/180 ))
 * d = 20 pixels per advancement ( SDLK_UP )
 */
    
    sprite.x = sprite.x + ( int )( MOVE_DISTANCE * cos(
            sprite.angle * ( M_PI / 180 )));
    sprite.y = sprite.y + ( int )( MOVE_DISTANCE * sin(
            sprite.angle * ( M_PI / 180 )));
}


void update_orientation(TurnDirection direction) {
/* update_orientation will turn the sprite either
 * left or right 45 degrees [ for now ]; if sprite.angle
 * >= 360, change angle to 0...if sprite.angle less than
 * 0, change angle to 315 [ prevents changing to 360 when angle
 * is actually 0 ]
 */
    // Turns are backwards due to SDL window coordinate system
    // (0,0) is in the top left corner; postive x to right;
    // positive y down;
    if (direction == TURN_LEFT) {
        sprite.turn = TURN_LEFT;
        sprite.angle = ( sprite.angle - 45 + 360 ) % 360; 
    } else {
        sprite.turn = TURN_RIGHT;
        sprite.angle = ( sprite.angle + 45 ) % 360;
        
    }
}


void update_pen( bool pen_state ) {
    sprite.pen = pen_state;
}


void draw_line(int x1, int y1, int x2, int y2) {
    // Set the line drawing color
    SDL_SetRenderTarget(renderer, lineTexture); // Render to line texture
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black color for the line

    // Draw the line to the texture
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

    // Reset the render target to the default
    SDL_SetRenderTarget(renderer, NULL);
}