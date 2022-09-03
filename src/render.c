/*
File:           render.c
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Rendering engine for the game.
*/

#include <gb/gb.h>

#include "tilemap_grid.h"

/*
** Initializes the game grid.
*/
void render_init_grid() {
    set_bkg_data(0, 0, tilemap_grid_tilemap);
}