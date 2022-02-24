/// file: bracetopia.c
/// bracetopia.c is the main entry point for the bracetopia project
/// author: Tom Schollenberger
///

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <getopt.h>
#include "board.h"

static const char USAGE_MESSAGE[] = "usage:\nbracetopia [-h] [-t N] [-c N] [-d dim] [-s %%str] [-v %%vac] [-e %%end]";
static char LINE_ONE[] = "Option      Default   Example   Description";
static char LINE_TWO[] = "'-h'        NA        -h        print this usage message.";
static char LINE_THREE[] = "'-t N'      900000    -t 5000   microseconds cycle delay.";
static char LINE_FOUR[] = "'-c N'      NA        -c4       count cycle maximum value.";
static char LINE_FIVE[] = "'-d dim'    15        -d 7      width and height dimension.";
static char LINE_SIX[] = "'-s %str'   50        -s 30     strength of preference.";
static char LINE_SEVEN[] = "'-v %vac'   20        -v30      percent vacancies.";
static char LINE_EIGHT[] = "'-e %endl'  60        -e75      percent Endline braces. Others want Newline.";

void set_spaces_numbers(int dimension, int vacancy_percentage, int endline_percentage, int *end_num, int *new_num) {
    int size = dimension * dimension;
    int vac_num = (int)(size * ((double)vacancy_percentage / 100));
    *end_num = (int)((size - vac_num) * ((double)endline_percentage / 100));
    *new_num = (int)((size - vac_num) - *end_num);
}

void output(int happiness_strength, int dimensions, int end_percent, int vacancy_percent, int cycle, int moves_this_cycle) {
    printf("cycle: %d\n", cycle);
    printf("moves this cycle: %d\n", moves_this_cycle);
    printf("dim: %d, %%strength of preference:  %d%%, %%vacancy:  %d%%, %%end:  %d%%", dimensions, happiness_strength, vacancy_percent, end_percent);
}

void output_ncurses(int happiness_strength, int dimensions, int end_percent, int vacancy_percent, int cycle, int moves_this_cycle) {
    printw("cycle: %d\n", cycle);
    printw("moves this cycle: %d\n", moves_this_cycle);
    printw("dim: %d, %%strength of preference:  %d%%, %%vacancy:  %d%%, %%end:  %d%%", dimensions, happiness_strength, vacancy_percent, end_percent);
}

void handle_print_cycle(int num_cycles, int size, char board[][MAX_SIZE], int happiness_strength, int dimensions, int end_percent, int vacancy_percent) {
    int cycle = 0;
    int moves_this_cycle = 0;

    output(happiness_strength, dimensions, end_percent, vacancy_percent, cycle, moves_this_cycle);
    cycle++;

    for (int i = 0; i < num_cycles; i++) {
        moves_this_cycle = update_board(size, board, happiness_strength);
        output(happiness_strength, dimensions, end_percent, vacancy_percent, cycle, moves_this_cycle);
        cycle++;
    }
}

void handle_infinite_cycle(int size, char board[][MAX_SIZE], int happiness_strength, int dimensions, int end_percent, int vacancy_percent, int delay) {
    initscr();

    int cycle = 0;
    int moves_this_cycle = 0;
    while (1) {
        move(0, 0);

        print_board_ncurses(size, board);
        move(size, 0);
        output_ncurses(happiness_strength, dimensions, end_percent, vacancy_percent, cycle, moves_this_cycle);
        refresh();

        moves_this_cycle = update_board(size, board, happiness_strength);
        cycle++;

        usleep(delay);
    }

    endwin();
}

int main(int argc, char *argv[]) {
    int delay = 900000;
    int dimension = 15;
    int strength = 50;
    int vacancy_percentage = 20;
    int endline_percentage = 60;
    int print_cycle_count = -1;

    int opt;

    if (argc == 0) {
        fprintf(stderr, USAGE_MESSAGE);
        return(EXIT_FAILURE);
    }

    while ((opt = getopt(argc, argv, "hd:v:s:e:c:t:")) != -1) {
        switch ( opt ) {
            case 'h':
                printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", USAGE_MESSAGE, LINE_ONE, LINE_TWO, LINE_THREE, 
                    LINE_FOUR, LINE_FIVE, LINE_SIX, LINE_SEVEN, LINE_EIGHT
                );
                break;
            case 'd': // handle dimension setting
                dimension = (int)strtol(optarg, NULL, 10);
                if (dimension < 5) { // min size is 5
                    dimension = 5;
                } else if (dimension > 39) { // max size is 39
                    dimension = 39;
                }
                
                break;
            case 's': // handle dimension setting
                strength = (int)strtol(optarg, NULL, 10);
                if (strength < 0) { // min size is 5
                    strength = 0;
                } else if (strength > 100) { // max size is 39
                    strength = 100;
                }
                
                break;
            case 'v': // handle dimension setting
                vacancy_percentage = (int)strtol(optarg, NULL, 10);
                if (vacancy_percentage < 0) { // min size is 5
                    vacancy_percentage = 0;
                } else if (vacancy_percentage > 100) { // max size is 39
                    vacancy_percentage = 100;
                }
                
                break;
            case 'e': // handle dimension setting
                endline_percentage = (int)strtol(optarg, NULL, 10);
                if (endline_percentage < 0) { // min size is 5
                    endline_percentage = 0;
                } else if (endline_percentage > 100) { // max size is 39
                    endline_percentage = 100;
                }

                break;
            case 'c': // handle dimension setting
                print_cycle_count = (int)strtol(optarg, NULL, 10);

                break;
            case 't':
                if ((int)strtol(optarg, NULL, 10) > 0) {
                    delay = (int)strtol(optarg, NULL, 10);
                }
                break;
            default:
                // some unknown, possibly unacceptable option flag
                fprintf(stderr, USAGE_MESSAGE);
                return (EXIT_FAILURE);
        }
    }

    int endline_num;
    int newline_num;

    set_spaces_numbers(dimension, vacancy_percentage, endline_percentage, &endline_num, &newline_num);

    // printf("%d %d %d %d\n", endline_num, newline_num, dimension * dimension, delay);

    char board[MAX_SIZE][MAX_SIZE];
    create_board(board, dimension, endline_num, newline_num);

    if (print_cycle_count > -1) {
        handle_print_cycle(print_cycle_count, dimension, board, strength, dimension, endline_percentage, vacancy_percentage);
    } else {
        handle_infinite_cycle(dimension, board, strength, dimension, endline_percentage, vacancy_percentage, delay);
    }

    return EXIT_SUCCESS;
}