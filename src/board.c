/*
File:           board.c
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Represents the current game board.
*/

#include <stddef.h>

#include "board.h"

/*
** Initializes a board
** @param board Board to initialize
*/
void board_init(Board* board) {
    board->score = 0;
    // TODO fill with random IDs
    for (size_t r=0; r<BOARD_SIZE; ++r) {
        for (size_t c=0; c<BOARD_SIZE; ++c) {
            board->grid[r][c] = 0;
        }
    }
    // TODO rm hard-coding
    board->grid[0][0] = 1;
    board->grid[1][1] = 12;
}