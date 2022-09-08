/*
File:           render.c
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Rendering engine for the game.
*/

#include <gb/gb.h>
#include <stdio.h>
#include <stddef.h>

#include "board.h"
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
    // Set the sprite mode for elongated sprites. This is a more efficient use
    // of limited sprite memory for this use case.
    SPRITES_8x16;

    // Load the game sprite tiles in
    set_sprite_data(0, MAX_SPRITE_TILES, spriteset_tiles);
    for (size_t i=0; i<MAX_TILE_ID; ++i) {
        set_sprite_tile(i, i * 2);
    }

    // Render the initial sprite data
    for (size_t r=0; r<BOARD_SIZE; ++r) {
        for (size_t c=0; c<BOARD_SIZE; ++c) {
            const TileId tileId = board->grid[r][c];
            if (tileId != NULL_TILE_ID) {
                const BoardPosition boardPos = { .row=r, .col=c };
                render_grid_tile(tileId, &boardPos);
            }
        }
    }

    SHOW_SPRITES;
}

/*
** Renders a single grid tile
** @param tileId    Tile to render
** @param boardPos  Board position to render the tile at
*/
void render_grid_tile(const TileId tileId, const BoardPosition* boardPos) {
    Position pos;
    grid_tile_calc_xy_pos(boardPos, &pos);
    SpriteId spriteId;
    grid_tile_calc_sprite_idx(tileId, &spriteId);
    // TODO rm
    //printf("tileIdx: %d|%d\n", spriteId.left, spriteId.right);
    // As the "null tile" is reserved and tileIds are equivalents to powers
    // of two, the left sprite ID is 1 less than the tile ID.
    move_sprite(spriteId.left, pos.x, pos.y);
    move_sprite(spriteId.right, pos.x + SPRITE_WIDTH, pos.y);
}