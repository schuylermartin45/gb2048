/*
File:           render.h
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Rendering engine for the game.
*/
#ifndef RENDER_H
#define RENDER_H

#include "board.h"

/***** Constants *****/
#define MAX_TILE_SPRITES    (MAX_TILE_ID * 2)

/***** Functions *****/

/// Initializes the game grid.
void render_init_grid();

/// Initializes the game board sprites
void render_init_board(const Board* board);

#endif