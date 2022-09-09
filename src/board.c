/*
File:           board.c
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Represents the current game board.
*/

#include <gb/gb.h>
#include <gb/hardware.h>
#include <rand.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#include "board.h"

/*
** Generate a new tile on the board.
** @param board Board to modify
*/
void board_generate_tile(Board* board) {
    // Decide if we are dropping a 2 or a 4, biased towards 2 (roughly 88% of
    // the time...Great Scott!)
    const TileId tileId = (rand() < 225) ? 1 : 2;
    while (true) {
        const uint8_t row = rand() % BOARD_SIZE;
        const uint8_t col = rand() % BOARD_SIZE;
        if (board->grid[row][col] == NULL_TILE_ID) {
            board->grid[row][col] = tileId;
            return;
        }
    }
}

/*
** Initializes a board
** @param board Board to initialize
*/
void board_init(Board* board) {
    // Initialize the board to 0
    board->score = 0;
    for (size_t r=0; r<BOARD_SIZE; ++r) {
        for (size_t c=0; c<BOARD_SIZE; ++c) {
            board->grid[r][c] = 0;
        }
    }
    
    // Two tiles are generated at random at the start.
    board_generate_tile(board);
    board_generate_tile(board);
}