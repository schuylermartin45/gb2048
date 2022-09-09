/*
File:           render_utils.h
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Rendering engine primatives and utilities. Breaks dependency cycles.
*/
#ifndef RENDER_UTILS_H
#define RENDER_UTILS_H

#include <stdint.h>

/***** Constants *****/

// Sprite dimenions in 8x16 mode
#define SPRITE_WIDTH    8
#define SPRITE_HEIGHT   16
// Padding between grid-tiles
#define TILE_PAD_X      16
#define TILE_PAD_Y      8
// Starting position for the upper-left-most grid tile
#define GRID_START_X    44
#define GRID_START_Y    48
// Invalid sprite positions that remove sprites from the viewport
// According to the docs, setting the Y out of bounds is preferred.
#define HIDE_SPRITE_X   0
#define HIDE_SPRITE_Y   0

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
