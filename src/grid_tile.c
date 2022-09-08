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
    pos->x = (boardPos->col * (SPRITE_WIDTH + 16)) + (GRID_START_X * 2);
    pos->y = (boardPos->row * (SPRITE_HEIGHT + 16)) + GRID_START_Y;
}

/*
** Calculate the index of the leading sprite 
** @param tileId    ID/value of the tile
** @param Sprite index of the two sprites that make up a grid-tile
*/
void grid_tile_calc_sprite_idx(const TileId tileId, SpriteId* spriteId) {
    spriteId->left = (tileId - 1) * 2;
    spriteId->right = spriteId->left + 1;
}