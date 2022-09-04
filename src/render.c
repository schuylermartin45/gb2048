/*
File:           render.c
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Rendering engine for the game.
*/

#include <gb/gb.h>

#include "tileset_grid.h"
#include "tilemap_grid.h"

/*
** Initializes the game grid.
*/
void render_init_grid() {
    set_bkg_data(0, 7, tileset_grid);
    set_bkg_tiles(0, 0, tilemap_gridWidth, tilemap_gridHeight, tilemap_grid);

    // Render data and turn the screen on
    SHOW_BKG;
    DISPLAY_ON;
}