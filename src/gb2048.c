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

/***** Constants *****/

/// Slows down the primary gameplay loop
#define USER_INPUT_DELAY    100


/***** Functions *****/

/*
** Main entry point to the program
** @return Exit code...for historical reasons and to be "proper"
*/
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
        
        const uint8_t buttons = joypad();
        if      (buttons & J_UP)    direction = BOARD_UP;
        else if (buttons & J_DOWN)  direction = BOARD_DOWN;
        else if (buttons & J_LEFT)  direction = BOARD_LEFT;
        else if (buttons & J_RIGHT) direction = BOARD_RIGHT;
        else if (buttons & J_START) {
            // TODO make a better pause menu        
            printf("\n\n\n\n\n\n\n\n     | Paused |\n");
            delay(USER_INPUT_DELAY);
            waitpad(J_START);
            delay(USER_INPUT_DELAY);
            cls();
            continue;
        }

        if (direction != BOARD_NONE) {
            // Only delay if user input has been detected.
            delay(USER_INPUT_DELAY);
            board_shift(&board, direction);
            render_board(&board);
        }
        
        wait_vbl_done();
    }

    return EXIT_SUCCESS;
}