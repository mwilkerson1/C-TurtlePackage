
/*
 * Interactive Turtle Graphics Program By Matthew Wilkerson
 * ---------------------------------------------------------
 * 
 * Overview:
 * ---------
 * This C program implements an interactive turtle graphics system using SDL2 for window management 
 * and OpenGL for rendering. Inspired by the classic "turtle graphics" concept, the program allows 
 * users to control the movement and orientation of a sprite ("turtle") on a 2D canvas by using 
 * keyboard inputs. As the turtle moves, it can optionally draw lines, enabling the user to create 
 * intricate graphical patterns interactively.
 * 
 * The primary features of this program include:
 * 1. Interactive control of a sprite's movement, including turning and moving forward.
 * 2. Drawing lines while the sprite moves, depending on whether the pen is down or up.
 * 3. Displaying the sprite as an image that moves and rotates based on user inputs.
 * 
 * Key Concepts:
 * -------------
 * 1. **Sprite Movement and Orientation**:
 *    - The turtle (or sprite) moves across the screen in a straight line when the user presses the 
 *      "Up" arrow key. The movement is determined by the current orientation of the turtle, which 
 *      can be rotated by pressing the "Left" or "Right" arrow keys.
 *    - The movement and rotation of the turtle are handled by calculating the x and y coordinates 
 *      using trigonometric functions. The turtle's angle is tracked and updated each time it turns.
 * 
 * 2. **Drawing Lines**:
 *    - The turtle can either draw lines while moving or move without drawing, controlled by the 
 *      "Pen Down" (`d`) and "Pen Up" (`u`) commands.
 *    - When the pen is down, each movement of the turtle results in a line being drawn on the screen.
 *    - The program maintains a list of all drawn lines to ensure that lines remain visible even 
 *      as the screen is updated with new frames.
 * 
 * 3. **Rendering with OpenGL**:
 *    - The program utilizes OpenGL for rendering the lines and sprite, leveraging the GPU for efficient 
 *      graphics rendering.
 *    - The OpenGL `glDrawPixels()` function is used to render the sprite image, while lines are rendered 
 *      using `glBegin(GL_LINES)` and subsequent vertex definitions.
 * 
 * User Input:
 * -----------
 * The following keyboard commands are supported to interact with the turtle:
 * - **Arrow Keys**:
 *   - `Left Arrow` (`←`): Rotate the turtle 45 degrees to the left.
 *   - `Right Arrow` (`→`): Rotate the turtle 45 degrees to the right.
 *   - `Up Arrow` (`↑`): Move the turtle forward by a predefined distance (`MOVE_DISTANCE`).
 * - **Pen Control**:
 *   - `d`: Pen Down - The turtle will draw lines as it moves.
 *   - `u`: Pen Up - The turtle will move without drawing lines.
 * - **Escape Key**:
 *   - `Esc`: Exit the program.
 * 
 * Dependencies:
 * -------------
 * - **SDL2**: Used for managing the window, handling events, and loading the sprite image. SDL2 provides 
 *   the basic framework for user interaction, including creating a window and listening for keyboard input.
 * - **OpenGL (GL and GLU)**: Used for rendering the graphics (lines and sprite). OpenGL is a cross-platform 
 *   API for rendering 2D and 3D vector graphics.
 * - **Math Library** (`math.h`): Provides trigonometric functions (`cos()`, `sin()`) that are used to calculate 
 *   the sprite's new position based on its angle.
 * 
 * Implementation Details:
 * -----------------------
 * - **Initialization**:
 *   - The program starts by initializing SDL and creating an OpenGL context for rendering.
 *   - The sprite image is loaded using SDL and is later rendered with OpenGL.
 *   - The OpenGL context is set up to use orthographic projection (`gluOrtho2D`) to create a simple 
 *     2D rendering environment.
 * 
 * - **Event Loop**:
 *   - The program runs an event loop (`event_loop()` function) that listens for user inputs.
 *   - Each user input (e.g., key press) triggers a corresponding action, such as moving the turtle, 
 *     rotating it, or toggling the pen state.
 *   - After processing events, the program clears the screen, redraws all previously drawn lines, 
 *     and renders the sprite in its new position.
 * 
 * - **Drawing and Rendering**:
 *   - **Drawing Lines**: When the pen is down, each movement results in a new line being added to 
 *     the list of lines (`lines` array). All lines are rendered on each frame to ensure they remain 
 *     visible.
 *   - **Rendering the Sprite**: The sprite is rendered using `glDrawPixels()` with its position and 
 *     orientation updated based on user input.
 *   - **Double Buffering**: The program uses double buffering (`SDL_GL_SwapWindow()`) to prevent 
 *     flickering, ensuring smooth visuals.
 * 
 * Limitations:
 * ------------
 * - **Line Storage Limit**: The current implementation limits the number of lines that can be drawn 
 *   to `1000`. This could be adjusted by modifying the size of the `lines` array or implementing a 
 *   dynamic storage system.
 * - **Orthographic Projection**: The OpenGL setup uses orthographic projection, which means that only 
 *   2D graphics are supported. The program does not currently support 3D transformations.
 * - **Image Format**: The sprite image must be in BMP format, as loaded using SDL's `SDL_LoadBMP()` 
 *   function. This could be extended to support other image formats.
 * 
 * TODO:
 * ------------
 * - Dynamic line storage
 * - Smooth rotation
 * - On screen UI to display pen status, etc...
 * - Create turtle sprite
 *
 */


/**********LIBRARIES**********/
#include <SDL2/SDL.h>  // SDL2 library for window management and events
#include <GL/gl.h>     // OpenGL library for rendering graphics
#include <GL/glu.h>    // OpenGL utility library for additional functions like setting the view
#include <stdio.h>
#include <stdbool.h>


/**********MACROS**********/
#define X_START 400           // Initial x-coordinate of the sprite
#define Y_START 400           // Initial y-coordinate of the sprite
#define MOVE_DISTANCE 20      // Number of pixels the sprite moves per step
#define PEN_START false       // Initial pen state (pen up)
#define IMG "/home/milkiwilki/Documents/School/csc451/C-TurtlePackage/Images/blackbuck.bmp" // Path to the sprite image
#define IMG_W 50              // Width of the sprite image
#define IMG_H 50              // Height of the sprite image


/***********STRUCTS & ENUMS**********/
// Enum representing possible turn directions
typedef enum {
    TURN_LEFT = 0,
    TURN_RIGHT = 1
} TurnDirection;


// Struct representing the sprite's properties
typedef struct {
    int x;                  // Current x-coordinate of the sprite
    int y;                  // Current y-coordinate of the sprite
    int angle;              // Current angle (orientation) of the sprite
    TurnDirection turn;     // Last turn direction
    bool pen;               // Whether the pen is down or up
} Sprite;


// Struct representing a line with start and end coordinates
typedef struct {
    int x1, y1, x2, y2;
} Line;


/**********FUNCTION PROTOTYPES**********/
bool init();                              // Initialize SDL
bool window_test_handler();               // Create SDL window and OpenGL context
void kill();                              // Clean up SDL and OpenGL resources
bool event_loop();                        // Main event handling loop
bool load_sprite(char* bmp);              // Load the sprite image
void update_location();                   // Update the sprite's location based on its orientation
void update_orientation(TurnDirection direction); // Update the sprite's orientation (turn left/right)
void update_pen(bool pen_state);          // Update the pen state (down or up)
void draw_line(int x1, int y1, int x2, int y2);   // Draw a line between two points
void setup_opengl();                      // Set up OpenGL settings for rendering


/**********GLOBAL VARIABLES**********/
SDL_Window* window;               // SDL window pointer
SDL_GLContext glContext;          // OpenGL context for rendering
SDL_Surface* spriteSurface;       // SDL surface for storing sprite image
Sprite sprite;                    // Sprite instance containing position and state
Line lines[1000];  // Array to store all the lines drawn
int lineCount = 0;                // Number of lines currently drawn


/**********MAIN**********/
int main(int argc, char* argv[]) {
    // Initialize sprite properties
    sprite.x = X_START;
    sprite.y = Y_START;
    sprite.pen = PEN_START;

    // Initialize SDL and OpenGL and create window
    if (!init()) return 1;
    if (!window_test_handler()) return 1;

    // Cleanup before shutting down
    printf("SHUTTING DOWN\n");
    kill();

    return 0;
}


/**********FUNCTIONS**********/
bool init() {
 /**
 * Initializes SDL with video and events support.
 * 
 * @return true if successful, false if initialization failed
 */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) > 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return false;
    }

    return true;
}


bool window_test_handler() {
/**
 * Creates SDL window, OpenGL context, and runs the main event loop.
 * 
 * @return true if successful, false otherwise
 */
    // Create SDL window with OpenGL support
    window = SDL_CreateWindow(
        "Interactive Turtle Graphics",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800,
        800,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Error creating window: %s\n", SDL_GetError());
        return false;
    }

    // Create OpenGL context for rendering in the window
    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        printf("Error creating OpenGL context: %s\n", SDL_GetError());
        return false;
    }

    // Set up OpenGL settings
    setup_opengl();

    // Load sprite image
    if (!load_sprite(IMG)) return false;

    // Run the event loop for interaction
    while (event_loop()) {
        SDL_Delay(10);
    }

    return true;
}


void kill() {
/**
 * Cleans up SDL and OpenGL resources before exiting the program.
 */
    if (spriteSurface) {
        SDL_FreeSurface(spriteSurface);
    }
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


bool event_loop() {
/**
 * Main event loop to handle keyboard inputs and redraw the scene.
 * 
 * @return false to exit the loop, true to continue
 */
    SDL_Event evt;
    static int previous_x = X_START;
    static int previous_y = Y_START;

    // Process all pending events
    while (SDL_PollEvent(&evt) != 0) {
        switch (evt.type) {
            case SDL_QUIT:
                return false; // Exit on quit event
            case SDL_KEYDOWN:
                switch (evt.key.keysym.sym) {
                    case SDLK_RIGHT:
                        printf("ROTATE 45 DEGREES RIGHT\n");
                        update_orientation(TURN_RIGHT);
                        break;
                    case SDLK_LEFT:
                        printf("ROTATE 45 DEGREES LEFT\n");
                        update_orientation(TURN_LEFT);
                        break;
                    case SDLK_UP:
                        printf("ADVANCE FORWARD\n");
                        previous_x = sprite.x;
                        previous_y = sprite.y;
                        update_location();
                        if (sprite.pen) {
                            draw_line(previous_x, previous_y, sprite.x, sprite.y);
                        }
                        break;
                    case SDLK_d:
                        printf("PEN DOWN\n");
                        update_pen(true);
                        break;
                    case SDLK_u:
                        printf("PEN UP\n");
                        update_pen(false);
                        break;
                    case SDLK_ESCAPE:
                        return false; // Exit on ESC key
                }
                break;
        }
    }

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw all previously drawn lines
    glColor3f(0.0f, 0.0f, 0.0f);  // Set line color to black
    glBegin(GL_LINES);
    for (int i = 0; i < lineCount; ++i) {
        glVertex2i(lines[i].x1, lines[i].y1);
        glVertex2i(lines[i].x2, lines[i].y2);
    }
    glEnd();

    // Draw the sprite image
    glRasterPos2i(sprite.x - IMG_W / 2, sprite.y - IMG_H / 2);
    glDrawPixels(IMG_W, IMG_H, GL_RGB, GL_UNSIGNED_BYTE, spriteSurface->pixels);

    // Swap buffers to display the current frame
    SDL_GL_SwapWindow(window);

    return true;
}


bool load_sprite(char* bmp) {
/**
 * Loads the sprite image from a BMP file and converts it to the appropriate format.
 * 
 * @param bmp Path to the BMP image file
 * @return true if successful, false otherwise
 */

    // Load the BMP image into an SDL surface
    spriteSurface = SDL_LoadBMP(bmp);

    // Check if the image was loaded successfully
    if (!spriteSurface) {
        printf("Error loading image: %s\n", SDL_GetError());
        return false;
    }

    // Convert the surface to RGB format
    SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(spriteSurface, SDL_PIXELFORMAT_RGB24, 0);
    SDL_FreeSurface(spriteSurface);
    spriteSurface = formattedSurface;

    // Check if format conversion was successful
    if (!spriteSurface) {
        printf("Error converting surface: %s\n", SDL_GetError());
        return false;
    }

    return true;
}


void update_location() {
/**
 * Updates the sprite's location based on its current orientation and movement distance.
 */
    sprite.x = sprite.x + (int)(MOVE_DISTANCE * cos(sprite.angle * (M_PI / 180)));
    sprite.y = sprite.y + (int)(MOVE_DISTANCE * sin(sprite.angle * (M_PI / 180)));
}


void update_orientation(TurnDirection direction) {
/**
 * Updates the sprite's orientation by turning it left or right by 45 degrees.
 * 
 * @param direction TURN_LEFT or TURN_RIGHT
 */
    if (direction == TURN_LEFT) {
        sprite.turn = TURN_LEFT;
        sprite.angle = (sprite.angle - 45 + 360) % 360; 
    } else {
        sprite.turn = TURN_RIGHT;
        sprite.angle = (sprite.angle + 45) % 360;
    }
}


void update_pen(bool pen_state) {
    sprite.pen = pen_state;
/**
 * Updates the pen state (down or up).
 * 
 * @param pen_state true for pen down, false for pen up
 */
}


void draw_line(int x1, int y1, int x2, int y2) {
/**
 * Draws a line between two points and stores it for persistent drawing.
 * 
 * @param x1 Starting x-coordinate
 * @param y1 Starting y-coordinate
 * @param x2 Ending x-coordinate
 * @param y2 Ending y-coordinate
 */
    if (lineCount < 1000) {
        lines[lineCount].x1 = x1;
        lines[lineCount].y1 = y1;
        lines[lineCount].x2 = x2;
        lines[lineCount].y2 = y2;
        lineCount++;
    }
}

/**
 * Sets up OpenGL settings such as the viewport, projection, and modelview matrices.
 */
void setup_opengl() {
/**
 * Sets up OpenGL settings such as the viewport, projection, and modelview matrices.
 */
    // Set the viewport
    glViewport(0, 0, 800, 800);

    // Set up the projection matrix for orthographic 2D rendering
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 800.0, 800.0, 0.0);

    // Set up the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set the clear color to a light green background
    glClearColor(0.39f, 1.0f, 0.2f, 1.0f);
}
