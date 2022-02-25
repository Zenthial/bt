/// output.c
/// handles all things related to the different print cycles
/// both infinite and standard print cycles are handled here
/// methods are relatively similar, except for the difference between printf and printw
/// author: tom schollenberger

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

#include "board.h"
#include "output.h"

/// prints the output message for the standard print cycle
void output(int happiness_strength, int dimensions, char board[][MAX_SIZE], int end_percent, int vacancy_percent, int cycle, int moves_this_cycle, float happiness_this_cycle) {
    print_board(dimensions, board);
    printf("cycle: %d\n", cycle);
    printf("moves this cycle: %d\n", moves_this_cycle);
    printf("teams' \"happiness\": %.4f\n", happiness_this_cycle);
    printf("dim: %d, %%strength of preference:  %d%%, %%vacancy:  %d%%, %%end:  %d%%\n", dimensions, happiness_strength, vacancy_percent, end_percent);
}

/// prints the ouput message for the infinite print cycle
void output_ncurses(int happiness_strength, int dimensions, int end_percent, int vacancy_percent, int cycle, int moves_this_cycle, float happiness_this_cycle) {
    printw("cycle: %d\n", cycle);
    printw("moves this cycle: %d\n", moves_this_cycle);
    printw("teams' \"happiness\": %.4f\n", happiness_this_cycle);
    printw("dim: %d, %%strength of preference:  %d%%, %%vacancy:  %d%%, %%end:  %d%%\n", dimensions, happiness_strength, vacancy_percent, end_percent);
    printw("Use Control-C to quit.\n");
}

/// handles the finite print cycle, program will end after this runs
void handle_print_cycle(int num_cycles, int size, char board[][MAX_SIZE], int happiness_strength, int end_percent, int vacancy_percent) {
    int cycle = 0;
    int moves_this_cycle = 0;
    float happiness_this_cycle = calculate_total_happiness(size, board, happiness_strength);

    output(happiness_strength, size, board, end_percent, vacancy_percent, cycle, moves_this_cycle, happiness_this_cycle);
    cycle++;

    for (int i = 0; i < num_cycles; i++) {
        update_board(size, board, happiness_strength, &moves_this_cycle, &happiness_this_cycle);
        output(happiness_strength, size, board, end_percent, vacancy_percent, cycle, moves_this_cycle, happiness_this_cycle);
        cycle++;
    }
}

/// handles the infinite print cycle, program can only be terminated with Control+C after this is called
void handle_infinite_cycle(int size, char board[][MAX_SIZE], int happiness_strength, int end_percent, int vacancy_percent, int delay) {
    initscr();

    int cycle = 0;
    int moves_this_cycle = 0;
    float happiness_this_cycle = calculate_total_happiness(size, board, happiness_strength);

    while (1) {
        move(0, 0);

        print_board_ncurses(size, board);
        move(size, 0);
        output_ncurses(happiness_strength, size, end_percent, vacancy_percent, cycle, moves_this_cycle, happiness_this_cycle);
        refresh();

        update_board(size, board, happiness_strength, &moves_this_cycle, &happiness_this_cycle);
        cycle++;

        usleep(delay);
    }

    endwin();
}