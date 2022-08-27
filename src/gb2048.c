/*
File:           gb2048.c
Author:         Schuyler Martin <schuylermartin45@github>

Description:    Main execution point of the program
*/
#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>

#include "utils.h"

int main() {
    for (uint8_t i=0; i<5; ++i) {
        printf("Hello, world!\n");
    }

    return EXIT_SUCCESS;
}