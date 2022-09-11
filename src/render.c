/*
File:           render.c
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Rendering engine for the game.
*/

#include <gb/gb.h>
#include <gb/cgb.h>
#include <gbdk/font.h>
#include <stdio.h>
#include <stddef.h>

#include "board.h"
#include "render.h"
#include "render_utils.h"

#include "spriteset_tiles.h"
#include "tileset_grid.h"
#include "tilemap_grid.h"

/***** Constants *****/

#define CUR_SPRITE_PALETTE  2

/// Default sprite palette for enhanced GBC graphics.
const uint16_t SPRITE_PALETTE[] = {
	0, RGB_BLUE, RGB_ORANGE, RGB_PINK,
	0, RGB_GREEN, RGB_BLUE, RGB_PURPLE,
	0, RGB_LIGHTGRAY, RGB_DARKGRAY, RGB_BLACK,
};

/***** Variables *****/

/// First/primary font used by the system.
font_t font_0;
/// Indicates how many characters are loaded in with the font.
uint8_t font_0_len;

/***** Functions *****/

/*
** Initializes font data for rendering the window layer. This should be the
** first initialization block.
*/
void render_init_font() {
    font_init();
    font_0 = font_load(font_spect);
    font_0_len = FONT_SPECT_LENGTH;
    font_set(font_0);
}

/*
** Initializes the game grid.
*/
void render_init_grid() {
    // TODO need to re-map background tiles now that they are pushed
    // back.
    set_bkg_data(font_0_len, 8, tileset_grid);
    set_bkg_tiles(0, 0, tilemap_gridWidth, tilemap_gridHeight, tilemap_grid);

    // Render data and turn the screen on
    SHOW_BKG;
    DISPLAY_ON;
}

/*
** Initializes the game board sprites
** @param board Game board to render
*/
void render_init_board(const Board* board) {
    // Set the sprite mode for elongated sprites. This is a more efficient use
    // of limited sprite memory for this use case.
    SPRITES_8x16;

    // Load the game sprite tiles in
    set_sprite_data(0, MAX_SPRITE_TILES, spriteset_tiles);
    set_sprite_palette(0, 3, SPRITE_PALETTE);
    
    // Render the initial sprite data
    render_board(board);

    SHOW_SPRITES;
}

/*
** Renders a single grid tile
** @param tile_id       Tile to render
** @param sprite_idx    Starting (left) sprite index
** @param board_pos     Board position to render the tile at
*/
void render_grid_tile(
    const TileId tile_id,
    const size_t sprite_idx,
    const BoardPosition* board_pos
) {
    SpriteId sprite_id;
    grid_tile_calc_sprite_idx(tile_id, &sprite_id);

    // There doesn't appear to be a way to hide sprites other than to move them
    // off the viewport. Upon next time the sprite gets a value, it will move to
    // the correct position and set to the correct sprite data.
    if (tile_id == NULL_TILE_ID) {
        move_sprite(sprite_idx, 0, 0);
        move_sprite(sprite_idx + 1, 0, 0);
        return;
    }

    Position pos;
    grid_tile_calc_xy_pos(board_pos, &pos);

    // Set the image data associated with the grid-tile value.
    set_sprite_tile(sprite_idx, sprite_id.left);
    set_sprite_tile(sprite_idx + 1, sprite_id.right);
    
    // TODO experiment with different sprite palettes
    set_sprite_prop(sprite_idx, CUR_SPRITE_PALETTE);
    set_sprite_prop(sprite_idx + 1, CUR_SPRITE_PALETTE);

    // As the "null tile" is reserved and `TileId`s are equivalents to powers
    // of two, the left sprite ID is 1 less than the tile ID.
    move_sprite(sprite_idx, pos.x, pos.y);
    move_sprite(sprite_idx + 1, pos.x + SPRITE_WIDTH, pos.y);
}

/*
** Renders a board
** @param board Game board to render
*/
void render_board(const Board* board) {
    /** Render the score **/
    render_window_show(false);
    uint8_t score_buff[WINDOW_STR_LEN_MAX + 1] = { '\0' };
    // Hide our 00-pad score cheating
    if (board->score) {
        sprintf(score_buff, "%d00", board->score);
    }
    else {
        sprintf(score_buff, "0", board->score);
    }
    render_str_relative(REL_POS_2, REL_POS_0, score_buff);
    render_str_relative(REL_POS_0, REL_POS_0, "Score:");
    
    /** Render the Board **/

    // For now, all sprites are associated with a fixed grid position and we
    // dynamically load the value of the sprite based on the value of the tile.
    size_t sprite_idx = 0;
    for (size_t r=0; r<BOARD_SIZE; ++r) {
        for (size_t c=0; c<BOARD_SIZE; ++c) {
            const TileId tile_id = board->grid[r][c];
            const BoardPosition board_pos = { .row=r, .col=c };
            render_grid_tile(tile_id, sprite_idx, &board_pos);
            // Increment by two as two half-grid-tiles are rendered per
            // iteration.
            sprite_idx += 2;
        }
    }
}

/** Window Mode: String and Menu Rendering **/

/*
** Shows the window layer.
** @param hide_sprites  (Optional) Optionally hide the sprite layer.
*/
void render_window_show(const bool hide_sprites) {
    SHOW_WIN;
    // If requested, hide sprites as they intersect with the window layer.
    if (hide_sprites) {
        HIDE_SPRITES;
    }
}

/* 
** Hides and clears the window layer
*/
void render_window_hide() {
    HIDE_WIN;
    SHOW_SPRITES;

    // Clear the window as to not leak visual data between rendering calls
    fill_win_rect(
        MIN_X_WND_TILE_POS,
        MIN_Y_WND_TILE_POS,
        MAX_X_WND_TILE_POS,
        MAX_Y_WND_TILE_POS,
        0x00
    );
}

/*
** Prepares a buffer for window string rendering
** @param str   String to render
** @param buff  Buffer to fill
** @return Length of the string that was rendered 
*/
uint8_t _render_init_str_buff(const uint8_t* str, uint8_t* buff) {
    uint8_t length = 0;

    // Prevent a buffer overflow by killing the loop if we've run out
    // of character buffer space.
    while (str[length] != '\0' && length < WINDOW_STR_LEN_MAX) {
        // Re-map the ASCII value to the index in the map
        buff[length] = str[length] - ASCII_FONT_IDX_DIFF;
        length++;
    }

    return length;
}

/*
** Renders a string to an X/Y tile coordinate, limited to one row of text
** @param x     X-Position of first tile, [0-31]
** @param y     Y-Position of first tile, [0-31]
** @param str   String to render
*/
void render_str_xy(const uint8_t x, const uint8_t y, const uint8_t* str) {
    uint8_t buff[WINDOW_STR_LEN_MAX];
    const uint8_t length = _render_init_str_buff(str, buff);

    set_win_tiles(x, y, length, 1, buff);
}

/*
** Renders a string with some relative positioning parameters
** @param x_rel Relative X positioning
** @param x_rel Relative Y positioning
** @param str   String to render
*/
void render_str_relative(
    const RelativeWindowPos x_rel,
    const RelativeWindowPos y_rel,
    const uint8_t* str
) {
    uint8_t buff[WINDOW_STR_LEN_MAX];
    const uint8_t length = _render_init_str_buff(str, buff);

    uint8_t x = 0;
    switch (x_rel) {
        case REL_POS_0:
            x = MIN_X_WND_TILE_POS;
            break;
        case REL_POS_1: {
            const uint8_t midpoint = (MAX_X_WND_TILE_POS - MIN_X_WND_TILE_POS) / 2;
            x =  midpoint - (length / 2);
            break;
        }
        case REL_POS_2:
            x = MAX_X_WND_TILE_POS - length;
            break;
    }

    uint8_t y = 0;
    switch (y_rel) {
        case REL_POS_0:
            y = MIN_Y_WND_TILE_POS;
            break;
        case REL_POS_1:
            y = (MAX_Y_WND_TILE_POS - MIN_Y_WND_TILE_POS) / 2;
            break;
        case REL_POS_2:
            y = MAX_Y_WND_TILE_POS;
            break;
    }

    set_win_tiles(x, y, length, 1, buff);
}