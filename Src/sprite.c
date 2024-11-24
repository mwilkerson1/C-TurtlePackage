#include "sprite.h"
#include <math.h>
#include <stdio.h>

// Global sprite variable
Sprite sprite;

// Movement and rotation increments
#define MOVE_INCREMENT 200.0f       // Pixels per second for movement

void update_location(float deltaTime, int windowWidth, int windowHeight) {
    // Calculate potential new position
    float deltaX = MOVE_INCREMENT * cos(sprite.angle * M_PI / 180.0f) * deltaTime;
    float deltaY = -MOVE_INCREMENT * sin(sprite.angle * M_PI / 180.0f) * deltaTime;  // Negative due to coordinate system

    float newX = sprite.x + deltaX;
    float newY = sprite.y + deltaY;

    // Calculate half sprite dimensions
    float halfWidth = 25.0f;  // IMG_W / 2.0f
    float halfHeight = 25.0f; // IMG_H / 2.0f

    // Check boundaries on X-axis
    if (newX - halfWidth < 0) {
        newX = halfWidth;
    } else if (newX + halfWidth > windowWidth) {
        newX = windowWidth - halfWidth;
    }

    // Check boundaries on Y-axis
    if (newY - halfHeight < 0) {
        newY = halfHeight;
    } else if (newY + halfHeight > windowHeight) {
        newY = windowHeight - halfHeight;
    }

    // Update sprite position
    sprite.x = newX;
    sprite.y = newY;
}

void update_orientation(TurnDirection direction) {
    // Not used in continuous rotation but kept for compatibility
}

void update_pen(bool pen_state) {
    sprite.pen = pen_state;
}

void change_color(int color_option) {
    switch (color_option) {
        case 1: // Black
            sprite.r = 0.0f;
            sprite.g = 0.0f;
            sprite.b = 0.0f;
            printf("Color changed to Black\n");
            break;
        case 2: // Blue
            sprite.r = 0.0f;
            sprite.g = 0.0f;
            sprite.b = 1.0f;
            printf("Color changed to Blue\n");
            break;
        case 3: // Red
            sprite.r = 1.0f;
            sprite.g = 0.0f;
            sprite.b = 0.0f;
            printf("Color changed to Red\n");
            break;
        case 4: // Green
            sprite.r = 0.0f;
            sprite.g = 1.0f;
            sprite.b = 0.0f;
            printf("Color changed to Green\n");
            break;
        case 5: // Yellow
            sprite.r = 1.0f;
            sprite.g = 1.0f;
            sprite.b = 0.0f;
            printf("Color changed to Yellow\n");
            break;
        default:
            printf("Invalid color option\n");
            break;
    }
}
