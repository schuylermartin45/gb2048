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


/*
** Helper function that centralizes the move logic for all 4 moves, handling
** the accumulation of values and the current score.
** @param cur     Current board position being examined
** @param next    Next board position in the direction of the move. This is
**                the position that is being accumulated into.
*/
void board_calc_move(Board* board, const BoardPosition* cur, const BoardPosition* next) {
	const TileId cur_val    = board->grid[cur->row][cur->col];
	const TileId next_val   = board->grid[next->row][next->col];
	// If the other value is 0, move the current value in
	if (board->grid[next->row][next->col] == NULL_TILE_ID) {
		board->grid[next->row][next->col] = cur_val;
		board->grid[cur->row][cur->col] = NULL_TILE_ID;
	}
    else if (cur_val == next_val) {
		// If the values are equal, accumulate
		board->grid[next->row][next->col]++;
		board->grid[cur->row][cur->col] = NULL_TILE_ID;
		// Score increments with the value accumulated
        // TODO probs need to adjust with powers of 2 simplification
		board->score += next_val;
	}
}

/*
** Shift a board in a given direction
** @param board     Board to modify
** @param direction Direction to shift in (can't be BOARD_NONE)
*/
void board_shift(Board* board, const BoardDirection direction) {
    // Reserve scratch space for board position information.
    BoardPosition cur;
    BoardPosition next;
    // Reduce duplicated code by iterating for 3 rows or columns
    for (size_t i=1; i<BOARD_SIZE; ++i) {
        switch (direction) {
            case BOARD_UP:
                break;
            case BOARD_DOWN:
                break;
            case BOARD_LEFT:
                break;
            case BOARD_RIGHT: {
                for (size_t r=0; r<BOARD_SIZE; ++r) {
                    for (size_t c=BOARD_SIZE-2; c>=0; --c) {
                        cur.row=r;  cur.col=c;
                        next.row=r; next.col=c+1;
                        board_calc_move(board, &cur, &next);
                    }
                }
                break;
            }
        }
    }

    // Add a new tile now that the shift is complete.
    board_generate_tile(board);
}