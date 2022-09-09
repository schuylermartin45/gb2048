/*
File:           gb2048.c
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Main execution point of the program
*/

#include <gb/gb.h>
#include <gbdk/console.h>
#include <rand.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "board.h"
#include "render.h"
#include "utils.h"

int main() {
    // TODO make splash screen
    printf("\n\n\n\n    Press start!\n");

    // Wait for the start-screen, then abuse the scanline register and seed
    // with a value derived by the current scan line value.
    waitpad(J_START);
    const uint16_t seed = LY_REG | (uint16_t)DIV_REG << 8;
    initarand(seed);
    cls();

    // Initialize game state
    Board board;
    board_init(&board);

    // Initialize the game rendering
    // TODO: Fix grid current/menu tile map is crap
    //render_init_grid();
    render_init_board(&board);

    while (true) {
        // Remap keys to directional enum
        BoardDirection direction = BOARD_NONE;
        // TODO: might make more sense to use `waitpad()` instead?
        const uint8_t buttons = waitpad(J_UP | J_DOWN | J_LEFT | J_RIGHT | J_START);
        if      (buttons & J_UP)    direction = BOARD_UP;
        else if (buttons & J_DOWN)  direction = BOARD_DOWN;
        else if (buttons & J_LEFT)  direction = BOARD_LEFT;
        else if (buttons & J_RIGHT) direction = BOARD_RIGHT;
        else if (buttons & J_START) {
            // TODO make a better pause menu        
            printf("\n\n\n\n   | Paused |\n");
            waitpad(J_START);
            cls();
            continue;
        }

        if (direction != BOARD_NONE) {
            board_shift(&board, direction);
            render_board(&board);
        }
        
        wait_vbl_done();
    }

    return EXIT_SUCCESS;
}