/*
File:           render.h
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Rendering engine for the game.
*/
#ifndef RENDER_H
#define RENDER_H

#include "board.h"

/***** Constants *****/
/// 2 (1 pair) of 8x16 sprites make up a grid-tile
#define MAX_SPRITE_PAIRS    (MAX_TILE_ID * 2)
/// 4 Tiles make up a grid-tile sprite
#define MAX_SPRITE_TILES    (MAX_TILE_ID * 4)

/***** Functions *****/

/// Initializes the game grid.
void render_init_grid();

/// Initializes the game board sprites
void render_init_board(const Board* board);

/// Renders a single grid tile
void render_grid_tile(const TileId tileId, const BoardPosition* boardPos);

#endif