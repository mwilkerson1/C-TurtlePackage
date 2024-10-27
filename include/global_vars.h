#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

#include <SDL2/SDL.h>
#include <stdbool.h>

// struct [Sprite]

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

/****************************************/
// Extern Global Variables
// Defined in main

extern SDL_Renderer* renderer;
extern SDL_Surface* winSurface;
extern SDL_Window* window;
extern Sprite sprite;

#endif // GLOBAL_VARS_H
