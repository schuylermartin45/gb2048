/*
File:           render.h
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Rendering engine for the game.
*/
#ifndef RENDER_H
#define RENDER_H

#include <stdbool.h>
#include <stddef.h>

#include "board.h"

/***** Constants *****/

/// 2 (1 pair) of 8x16 sprites make up a grid-tile
#define MAX_SPRITE_PAIRS    (MAX_TILE_ID * 2)
/// 4 Tiles make up a grid-tile sprite
#define MAX_SPRITE_TILES    (MAX_TILE_ID * 4)

/// Number of grid tiles visible on a full board
#define BOARD_NUM_GRID_TILES    (BOARD_SIZE * BOARD_SIZE)
/// Number of sprites visible on a full board
#define BOARD_NUM_GRID_SPRITES  (BOARD_NUM_GRID_TILES * 2)


// Min and Max X/Y window locations, in tile-units
#define MIN_X_WND_TILE_POS  (MINWNDPOSX / 8)
#define MAX_X_WND_TILE_POS  (MAXWNDPOSX / 8)
#define MIN_Y_WND_TILE_POS  (MINWNDPOSY / 8)
#define MAX_Y_WND_TILE_POS  (MAXWNDPOSY / 8)

// Number of characters provided in various provided fonts.
#define FONT_MIN_LENGTH     37
#define FONT_SPECT_LENGTH   96

/// Current max string length for window string rendering
#define WINDOW_STR_LEN_MAX  18
/// Difference between an ASCII value and the font memory location
#define ASCII_FONT_IDX_DIFF 32

/***** Types *****/

/// Enums that represent relative positioning. Roughly follows "Rule of 3rds"
typedef enum {
    REL_POS_0, // Top/Left
    REL_POS_1, // Middle
    REL_POS_2, // Bottom/Right
} RelativeWindowPos;

/***** Functions *****/

/// Initializes font data for rendering the window layer
void render_init_font();
/// Initializes the game grid.
void render_init_grid();
/// Initializes the game board sprites
void render_init_board(const Board* board);

/// Renders a single grid tile
void render_grid_tile(
    const TileId tile_id,
    const size_t sprite_idx,
    const BoardPosition* board_pos
);
/// Renders a board
void render_board(const Board* board);


/** Window Mode: String and Menu Rendering **/

/// Shows the window layer
void render_window_show(const bool hide_sprites);
/// Hides and clears the window layer
void render_window_hide();

/// Renders a string to an X/Y tile coordinate
void render_str_xy(const uint8_t x, const uint8_t y, uint8_t* str);
/// Renders a string with some relative positioning parameters
void render_str_relative(
    const RelativeWindowPos x_rel,
    const RelativeWindowPos y_rel,
    const uint8_t* str
);

#endif