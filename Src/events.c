#include "events.h"
#include "sprite.h"
#include "graphics.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

// Key state variables for continuous movement and rotation
static bool keyLeftPressed = false;
static bool keyRightPressed = false;
static bool keyUpPressed = false;

// Movement and rotation increments
#define ROTATION_INCREMENT 90.0f    // Degrees per second for rotation
#define MOVE_INCREMENT 200.0f       // Pixels per second for movement

bool handle_events(float deltaTime, int* windowWidth, int* windowHeight) {
    SDL_Event evt;

    // Process all pending events
    while (SDL_PollEvent(&evt) != 0) {
        switch (evt.type) {
            case SDL_QUIT:
                return false; // Exit on quit event
            case SDL_KEYDOWN:
                switch (evt.key.keysym.sym) {
                    case SDLK_RIGHT:
                        keyRightPressed = true;
                        break;
                    case SDLK_LEFT:
                        keyLeftPressed = true;
                        break;
                    case SDLK_UP:
                        keyUpPressed = true;
                        break;
                    case SDLK_d:
                        update_pen(true);
                        break;
                    case SDLK_u:
                        update_pen(false);
                        break;
                    case SDLK_1:
                        change_color(1);
                        break;
                    case SDLK_2:
                        change_color(2);
                        break;
                    case SDLK_3:
                        change_color(3);
                        break;
                    case SDLK_4:
                        change_color(4);
                        break;
                    case SDLK_5:
                        change_color(5);
                        break;
                    case SDLK_ESCAPE:
                        return false; // Exit on ESC key
                }
                break;
            case SDL_KEYUP:
                switch (evt.key.keysym.sym) {
                    case SDLK_RIGHT:
                        keyRightPressed = false;
                        break;
                    case SDLK_LEFT:
                        keyLeftPressed = false;
                        break;
                    case SDLK_UP:
                        keyUpPressed = false;
                        break;
                }
                break;
            case SDL_WINDOWEVENT:
                if (evt.window.event == SDL_WINDOWEVENT_RESIZED) {
                    *windowWidth = evt.window.data1;
                    *windowHeight = evt.window.data2;
                    printf("Window resized to %d x %d\n", *windowWidth, *windowHeight);

                    // Update OpenGL viewport and projection
                    glViewport(0, 0, *windowWidth, *windowHeight);
                    glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();
                    gluOrtho2D(0.0, *windowWidth, *windowHeight, 0.0);
                    glMatrixMode(GL_MODELVIEW);
                }
                break;
        }
    }

    // Update rotation
    if (keyLeftPressed) {
        sprite.angle = fmod(sprite.angle + ROTATION_INCREMENT * deltaTime, 360.0f);
    }
    if (keyRightPressed) {
        sprite.angle = fmod(sprite.angle - ROTATION_INCREMENT * deltaTime + 360.0f, 360.0f);
    }

    // Update position
    if (keyUpPressed) {
        float previous_x = sprite.x;
        float previous_y = sprite.y;
        update_location(deltaTime, *windowWidth, *windowHeight);
        if (sprite.pen) {
            // Add line to lines array
            extern void add_line(float x1, float y1, float x2, float y2);
            add_line(previous_x, previous_y, sprite.x, sprite.y);
        }
    }

    return true;
}
