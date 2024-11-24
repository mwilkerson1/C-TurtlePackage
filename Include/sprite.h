#ifndef SPRITE_H
#define SPRITE_H

#include <stdbool.h>
#include <GL/gl.h>

// Enum representing possible turn directions (not used in continuous movement but kept for compatibility)
typedef enum {
    TURN_LEFT = 0,
    TURN_RIGHT = 1
} TurnDirection;

// Struct representing the sprite's properties
typedef struct {
    float x;                  // Current x-coordinate of the sprite
    float y;                  // Current y-coordinate of the sprite
    float angle;              // Current angle (orientation) of the sprite
    TurnDirection turn;       // Last turn direction
    bool pen;                 // Whether the pen is down or up
    GLfloat r, g, b;          // Current drawing color (RGB components)
} Sprite;

// Externally accessible sprite variable
extern Sprite sprite;

// Function prototypes
void update_location(float deltaTime, int windowWidth, int windowHeight);
void update_orientation(TurnDirection direction);
void update_pen(bool pen_state);
void change_color(int color_option);

#endif // SPRITE_H
