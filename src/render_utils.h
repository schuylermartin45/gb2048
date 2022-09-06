/*
File:           render_utils.h
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Rendering engine primatives and utilities. Breaks dependency cycles.
*/
#ifndef RENDER_UTILS_H
#define RENDER_UTILS_H

#include <stdint.h>

/***** Constants *****/

#define SPRITE_WIDTH    8
#define SPRITE_HEIGHT   16
// TODO fix locations
#define GRID_START_X    8
#define GRID_START_Y    64

/***** Types *****/

/// Represents an X,Y pixel/tile position
typedef struct {
    uint8_t x;
    uint8_t y;
} Position;

/// Row/Column position on the board
typedef struct {
    uint8_t row;
    uint8_t col;
} BoardPosition;

/// Given a Position, calculate the next adjacent sprite
void render_utils_calc_adjacent_sprite(const Position* left, Position* right);

#endif
