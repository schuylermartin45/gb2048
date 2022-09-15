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
** Blocks on a single button press (held then released)
** @param mask  Button mask to wait on
** @return Button(s) that were pressed
*/
uint8_t wait_on_button_pressed(const uint8_t mask) {
    const uint8_t button = waitpad(mask);
    waitpadup();
    return button;
}

/*
** Main entry point to the program
** @return Exit code...for historical reasons and to be "proper"
*/
int main() {
    // Initialize font data first so we have it at the ready.
    render_init_font();

    // TODO make a better splash screen
    render_window_show(false);
    render_str_relative(REL_POS_1, REL_POS_0, "-- Gameboy 2048 --");
    render_str_relative(REL_POS_1, REL_POS_1, "Press start!");
    render_str_relative(REL_POS_1, REL_POS_2, "Schuyler M. - 2022");
    // Wait for the start-screen, then abuse the scanline register and seed
    // with a value derived by the current scan line value.
    wait_on_button_pressed(J_START | J_A);
    render_window_hide();
    const uint16_t seed = LY_REG | (uint16_t)DIV_REG << 8;
    initarand(seed);

    // Initialize game state
    Board board;
    board_init(&board);

    // Initialize the game rendering
    // TODO: Fix grid current/menu tile map is crap
    render_init_grid();
    render_init_board(&board);

    while (true) {
        // Remap keys to directional enum
        BoardDirection direction = BOARD_NONE;
        
        const uint8_t buttons = wait_on_button_pressed(J_UP|J_DOWN|J_LEFT|J_RIGHT|J_START); //joypad();
        if      (buttons & J_UP)    direction = BOARD_UP;
        else if (buttons & J_DOWN)  direction = BOARD_DOWN;
        else if (buttons & J_LEFT)  direction = BOARD_LEFT;
        else if (buttons & J_RIGHT) direction = BOARD_RIGHT;
        else if (buttons & J_START) {
            // TODO make a better pause menu
            render_window_show(true);
            render_str_relative(REL_POS_1, REL_POS_1, "Paused");
            // First wait (for any button) starts "pause mode". This second wait
            // keeps the pause menu open.
            wait_on_button_pressed(J_START);
            render_window_hide();
            continue;
        }

        if (direction != BOARD_NONE) {
            board_shift(&board, direction);
            const Endgame endgame = board_check(&board);
            render_board(&board);
            // Allow the final board to render then draw the menu
            if (endgame != ENDGAME_NONE) {
                render_window_show(true);
                switch (endgame) {
                    case ENDGAME_WIN_2048:
                        render_str_relative(
                            REL_POS_1,
                            REL_POS_1,
                            "2048! Continue?"
                        );
                    break;
                    case ENDGAME_WIN_4096:
                        render_str_relative(
                            REL_POS_1,
                            REL_POS_1,
                            "4096! Play again?"
                        );
                    break;
                    case ENDGAME_LOSS:
                        render_str_relative(
                            REL_POS_1,
                            REL_POS_1,
                            "Game Over."
                        );
                    break;
                }
                wait_on_button_pressed(J_START | J_A);
                render_window_hide();
                // Allow the user to play again
                if ((endgame == ENDGAME_WIN_4096) || (endgame == ENDGAME_LOSS)) {
                    board_init(&board);
                    render_board(&board);
                }
                continue;
            }
        }
        
        wait_vbl_done();
    }

    return EXIT_SUCCESS;
}