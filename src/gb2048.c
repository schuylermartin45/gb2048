/*
File:           gb2048.c
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Main execution point of the program
*/
#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "render.h"
#include "utils.h"

int main() {
    // Initialize the game grid rendering
    render_init_grid();

    while (true) {
        wait_vbl_done();
    }

    return EXIT_SUCCESS;
}