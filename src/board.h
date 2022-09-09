/*
File:           board.h
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Represents the current game board.
*/
#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>

#include "grid_tile.h"

/***** Constants *****/

#define MAX_TILE_ID 12
#define BOARD_SIZE  4

/***** Types *****/

/// Stores data associated with the current game
typedef struct {
    uint8_t score;
    TileId grid[BOARD_SIZE][BOARD_SIZE];
} Board;

typedef enum {
    BOARD_NONE,
    BOARD_UP,
    BOARD_DOWN,
    BOARD_LEFT,
    BOARD_RIGHT,
} BoardDirection;

/// Initializes a board
void board_init(Board* board);

/// Generate a new tile on the board.
void board_generate_tile(Board* board);

/// Shift a board in a direction
void board_shift(Board* board, const BoardDirection direction);

#endif