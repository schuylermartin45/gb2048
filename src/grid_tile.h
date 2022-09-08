/*
File:           grid_tile.h
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Represents a tile object on the grid
*/
#ifndef GRID_TILE_H
#define GRID_TILE_H

#include <stdint.h>

#include "render_utils.h"

/***** Constants *****/

/// Represents an unused grid tile
#define NULL_TILE_ID    0

/***** Types *****/

/// Represents a tile value on the grid (powers of 2). Can also be used
/// to index sprites.
typedef uint8_t TileId;

/// Identifies a grid tile by a left and a right 8x16 sprite.
typedef struct {
    uint8_t left;
    uint8_t right;
} SpriteId;

/***** Functions *****/

/// Calculate the rendering position of the tile, based on the current row/col 
void grid_tile_calc_xy_pos(const BoardPosition* boardPos, Position* pos);
/// Calculate the index of the leading sprite 
void grid_tile_calc_sprite_idx(const TileId tileId, SpriteId* spriteId);

#endif