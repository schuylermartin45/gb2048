/*
File:           render.c
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Rendering engine for the game.
*/

#include <gb/gb.h>
#include <gb/cgb.h>
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
uint16_t SPRITE_PALETTE[] = {
	0, RGB_BLUE, RGB_ORANGE, RGB_PINK,
	0, RGB_GREEN, RGB_BLUE, RGB_PURPLE,
	0, RGB_LIGHTGRAY, RGB_DARKGRAY, RGB_BLACK,
};

/***** Functions *****/

/*
** Initializes the game grid.
*/
void render_init_grid() {
    set_bkg_data(0, 8, tileset_grid);
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
** @param tileId    Tile to render
** @param spriteIdx Starting (left) sprite index
** @param boardPos  Board position to render the tile at
*/
void render_grid_tile(const TileId tileId, const size_t spriteIdx, const BoardPosition* boardPos) {
    SpriteId spriteId;
    grid_tile_calc_sprite_idx(tileId, &spriteId);

    // There doesn't appear to be a way to hide sprites other than to move them
    // off the viewport. Upon next time the sprite gets a value, it will move to
    // the correct position and set to the correct sprite data.
    if (tileId == NULL_TILE_ID) {
        move_sprite(spriteIdx, 0, 0);
        move_sprite(spriteIdx + 1, 0, 0);
        return;
    }

    Position pos;
    grid_tile_calc_xy_pos(boardPos, &pos);

    // Set the image data associated with the grid-tile value.
    set_sprite_tile(spriteIdx, spriteId.left);
    set_sprite_tile(spriteIdx + 1, spriteId.right);
    
    // TODO experiment with different sprite palettes
    set_sprite_prop(spriteIdx, CUR_SPRITE_PALETTE);
    set_sprite_prop(spriteIdx + 1, CUR_SPRITE_PALETTE);

    // As the "null tile" is reserved and tileIds are equivalents to powers
    // of two, the left sprite ID is 1 less than the tile ID.
    move_sprite(spriteIdx, pos.x, pos.y);
    move_sprite(spriteIdx + 1, pos.x + SPRITE_WIDTH, pos.y);
}

/*
** Renders a board
** @param board Game board to render
*/
void render_board(const Board* board) {
    // For now, all sprites are associated with a fixed grid position and we
    // dynamically load the value of the sprite based on the value of the tile.
    size_t spriteIdx = 0;
    for (size_t r=0; r<BOARD_SIZE; ++r) {
        for (size_t c=0; c<BOARD_SIZE; ++c) {
            const TileId tileId = board->grid[r][c];
            const BoardPosition boardPos = { .row=r, .col=c };
            render_grid_tile(tileId, spriteIdx, &boardPos);
            // Increment by two as two half-grid-tiles are rendered per
            // iteration.
            spriteIdx += 2;
        }
    }
}