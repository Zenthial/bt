/// file: bracetopia.c
/// bracetopia.c is the main entry point for the bracetopia project
/// author: Tom Schollenberger
///
#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <ncurses.h>

#include "board.h"
#include "output.h"
#include "options.h"

/// based on the endline and vacancy percentages, combined with the dimension,
/// calculates the newline and endline numbers
void get_spaces_numbers(int dimension, int vacancy_percentage, int endline_percentage, int *end_num, int *new_num) {
    int size = dimension * dimension;
    int vac_num = (int)(size * ((double)vacancy_percentage / 100));
    *end_num = (int)((size - vac_num) * ((double)endline_percentage / 100));
    *new_num = (int)((size - vac_num) - *end_num);
}

/// main entry point
int main(int argc, char *argv[]) {
    int delay = 900000;
    int dimension = 15;
    int strength = 50;
    int vacancy_percentage = 20;
    int endline_percentage = 60;
    int print_cycle_count = -1;

    int ret_val = get_options(argc, argv, &dimension, &strength, &vacancy_percentage,
                              &endline_percentage, &print_cycle_count, &delay);

    if (ret_val == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    else if (ret_val == -1)
    {
        return EXIT_SUCCESS;
    }

    int endline_num;
    int newline_num;

    get_spaces_numbers(dimension, vacancy_percentage, 
        endline_percentage, &endline_num, &newline_num);

    // printf("%d %d %d %d\n", endline_num, newline_num, dimension * dimension, delay);

    char board[MAX_SIZE][MAX_SIZE];
    create_board(dimension, board, endline_num, newline_num);

    if (print_cycle_count >= 0) {
        handle_print_cycle(print_cycle_count, dimension, board, 
            strength, endline_percentage, vacancy_percentage);
    } else {
        handle_infinite_cycle(dimension, board, strength, endline_percentage, vacancy_percentage, delay);
    }

    return EXIT_SUCCESS;
}