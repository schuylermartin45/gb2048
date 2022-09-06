/*
File:           grid_tile.c
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Represents a tile object on the grid
*/

#include "grid_tile.h"

/*
** Calculate the rendering position of the tile, based on the current row/col 
*/
void grid_tile_calc_xy_pos(const BoardPosition* boardPos, Position* pos) {
    // TODO fix math
    pos->x = (boardPos->row * SPRITE_WIDTH) + GRID_START_X;
    pos->y = (boardPos->col * SPRITE_HEIGHT) + GRID_START_Y;
}

/*
** Calculate the index of the leading sprite 
** @param tileId    ID/value of the tile
** @return Index of the left-hand sprite
*/
uint8_t grid_tile_calc_sprite_idx(const TileId tileId) {
    return (tileId - 1) * 2;
}