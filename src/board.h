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

// Macros used for board availability checks
#define ROW_4_BIT_MASK          0xF0
#define COL_4_BIT_MASK          0x0F
#define TILE_USED_TERMINATOR    0xFF

/***** Types *****/

/// Scoring will store a small number to then display a much bigger number.
typedef uint8_t Score;

/// Stores data associated with the current game
typedef struct {
    Score score;
    TileId grid[BOARD_SIZE][BOARD_SIZE];
} Board;

/// Directions the board can shift
typedef enum {
    BOARD_NONE,
    BOARD_UP,
    BOARD_DOWN,
    BOARD_LEFT,
    BOARD_RIGHT,
} BoardDirection;

/// Various end game scenarios.
typedef enum {
    ENDGAME_NONE,       // No change, continue testing
    ENDGAME_LOSS,       // Board is full
    ENDGAME_WIN_2048,   // The true ending
    ENDGAME_WIN_4096,   // The point where I gave up making sprites
} Endgame;

/// Initializes a board
void board_init(Board* board);

/// Generate a new tile on the board.
void board_generate_tile(Board* board);
/// Shift a board in a direction
void board_shift(Board* board, const BoardDirection direction);

/// Check if the game is over
Endgame board_check(const Board* board);

#endif