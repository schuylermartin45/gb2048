/*
File:           render.c
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Rendering engine for the game.
*/

#include <gb/gb.h>
#include <stddef.h>

#include "render.h"
#include "render_utils.h"

#include "spriteset_tiles.h"
#include "tileset_grid.h"
#include "tilemap_grid.h"

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
    // Load the game sprite tiles in
    set_sprite_data(0, MAX_TILE_SPRITES, spriteset_tiles);
    for (size_t i=0; i<MAX_TILE_SPRITES; ++i) {
        set_sprite_tile(i, i);
    }

    // Render the initial sprite data
    for (size_t r=0; r<BOARD_SIZE; ++r) {
        for (size_t c=0; c<BOARD_SIZE; ++c) {
            const TileId tileId = board->grid[r][c];
            if (tileId != NULL_TILE_ID) {
                const BoardPosition boardPos = { .row=r, .col=c };
                Position pos;
                grid_tile_calc_xy_pos(&boardPos, &pos);
                move_sprite(
                    tileId - 1,
                    pos.x,
                    pos.y
                );
            }
        }
    }

    SHOW_SPRITES;
}