#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
/*****PROJECT HEADERS*****/
#include "global_vars.h"
#include "sprite_logic.h"

#define MOVE_DISTANCE 20

// TODO: Add testing code and test functions

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

