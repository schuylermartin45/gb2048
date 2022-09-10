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

    // Scan for all available spots, storing the row value in the upper 4 bits
    // and the column in the lower 4 bits.
    uint8_t available[BOARD_SIZE * BOARD_SIZE] = { TILE_USED_TERMINATOR };
    size_t available_idx = 0;
    for (size_t r=0; r<BOARD_SIZE; ++r) {
        for (size_t c=0; c<BOARD_SIZE; ++c) {
            if (board->grid[r][c] == NULL_TILE_ID) {
                available[available_idx++] = r << 4 | c;
            }
        }
    }

    // No tile can be added, break early
    if (available_idx == 0) {
        return;
    }

    // Randomly pick an available position, then decode the row and column
    const uint8_t encoded_rc = available[rand() % available_idx];
    board->grid[encoded_rc >> 4][encoded_rc & COL_4_BIT_MASK] = tileId;
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
** @param is_noop Sets to false if an "action" occurred in this direction. Used
**                to detect "no-ops" in player actions.
*/
void board_calc_move(
    Board* board,
    const BoardPosition* cur,
    const BoardPosition* next,
    bool* is_noop
) {
	const TileId cur_val    = board->grid[cur->row][cur->col];
	const TileId next_val   = board->grid[next->row][next->col];
	// If the other value is 0, move the current value in
	if (board->grid[next->row][next->col] == NULL_TILE_ID) {
		board->grid[next->row][next->col] = cur_val;
		board->grid[cur->row][cur->col] = NULL_TILE_ID;
        *is_noop = false;
	}
    else if (cur_val == next_val) {
		// If the values are equal, accumulate
		board->grid[next->row][next->col]++;
		board->grid[cur->row][cur->col] = NULL_TILE_ID;
		// Score increments with the value accumulated
        // TODO probs need to adjust with powers of 2 simplification
		board->score += next_val;
        *is_noop = false;
	}
}

/*
** Shift a board in a given direction
** @param board     Board to modify
** @param direction Direction to shift in (can't be BOARD_NONE)
*/
void board_shift(Board* board, const BoardDirection direction) {
    const Score init_score = board->score;
    // Reserve scratch space for board position information.
    BoardPosition cur;
    BoardPosition next;
    bool is_noop = true;
    // Reduce duplicated code by iterating for 3 rows or columns
    for (size_t i=1; i<BOARD_SIZE; ++i) {
        switch (direction) {
            case BOARD_UP: {
                for (size_t r=1; r<BOARD_SIZE; ++r) {
                    for (size_t c=0; c<BOARD_SIZE; ++c) {
                        cur.row=r;  cur.col=c;
                        next.row=r-1; next.col=c;
                        board_calc_move(board, &cur, &next, &is_noop);
                    }
                }
                break;
            }
            case BOARD_DOWN: {
                // Canonically using `size_t` here will not work, so we will
                // use a counter that can go slightly negative.
                for (int8_t r=BOARD_SIZE-2; r>=0; --r) {
                    for (size_t c=0; c<BOARD_SIZE; ++c) {
                        cur.row=r;  cur.col=c;
                        next.row=r+1; next.col=c;
                        board_calc_move(board, &cur, &next, &is_noop);
                    }
                }
                break;
            }
            case BOARD_LEFT: {
                for (size_t r=0; r<BOARD_SIZE; ++r) {
                    for (size_t c=1; c<BOARD_SIZE; ++c) {
                        cur.row=r;  cur.col=c;
                        next.row=r; next.col=c-1;
                        board_calc_move(board, &cur, &next, &is_noop);
                    }
                }
                break;
            }
            case BOARD_RIGHT: {
                for (size_t r=0; r<BOARD_SIZE; ++r) {
                    for (int8_t c=BOARD_SIZE-2; c>=0; --c) {
                        cur.row=r;  cur.col=c;
                        next.row=r; next.col=c+1;
                        board_calc_move(board, &cur, &next, &is_noop);
                    }
                }
                break;
            }
        }
    }

    // TODO add sound when tiles have been combined.
    if (init_score != board->score) {
    }

    // Add a new tile now that the shift is complete and direction made a valid
    // "change" (i.e. the player action wasn't a "no-op").
    //
    // In other words: tiles are not added in the case where no new moves are
    // possible in that direction (tiles can't be combined and all current tiles
    // can't move in the requested direction)
    if (!is_noop) {
        board_generate_tile(board);
    }
}