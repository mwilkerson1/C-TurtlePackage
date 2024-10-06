#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

#include <SDL2/SDL.h>
#include <stdbool.h>

// Typedef enum [bool] and struct [Sprite]

typedef struct {
    int x;
    int y;
    int angle;
    bool pen;
} Sprite;

/****************************************/
// Extern Global Variables
// Defined in main

extern SDL_Renderer* renderer;
extern SDL_Window* window;

#endif // GLOBAL_VARS_H
