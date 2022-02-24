#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

#include "board.h"

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