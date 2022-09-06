/*
File:           render_utils.c
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Rendering engine primatives. Breaks dependency cycles.
*/

# include "render_utils.h"

/*
** Given a Position, calculate the next adjacent sprite
** @param left  Left sprite position (top left corner)
** @param right Resulting position of the adjacent sprite
*/
void render_utils_calc_adjacent_sprite(const Position* left, Position* right) {
    right->x = left->x + SPRITE_WIDTH;
    right->y = left->y;
}