/*
File:           board.c
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Represents the current game board.
*/

#include <gb/hardware.h>
#include <rand.h>
#include <stdio.h>
#include <stddef.h>

#include "board.h"

/*
** Initializes a board
** @param board Board to initialize
*/
void board_init(Board* board) {
    // TODO use the RTC? I can't remember what Pokemon uses
    const uint16_t seed = (uint16_t)DIV_REG << 8;
    initarand(seed);

    // TODO rm, this is just a test
    for (size_t i=0; i<5; ++i) {
        const uint8_t ranNum = rand();
        printf("Ran: %d\n", ranNum);
    }

    board->score = 0;
    // TODO fill with random IDs
    for (size_t r=0; r<BOARD_SIZE; ++r) {
        for (size_t c=0; c<BOARD_SIZE; ++c) {
            board->grid[r][c] = 0;
        }
    }
    // TODO rm hard-coding
    board->grid[0][0] = 1;
    board->grid[0][1] = 2;
    board->grid[0][2] = 3;
    board->grid[0][3] = 4;
    board->grid[1][0] = 1;
    board->grid[1][1] = 2;
    board->grid[1][2] = 0;
    board->grid[1][3] = 8;
    board->grid[2][0] = 9;
    board->grid[2][1] = 10;
    board->grid[2][2] = 11;
    board->grid[2][3] = 12;
}