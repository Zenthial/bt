/// board.c
/// handles all things related to the board state
/// author: tom schollenberger

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "board.h"

#define TRUE 1
#define FALSE 0
#define NEIGHBORS 8
#define VACANT '.'
#define END_LINE 'e'
#define NEW_LINE 'n'

/// determines if a given cell is happy
int is_happy(int strength, int x, int y, int size, char board[][MAX_SIZE]) {
    char type = board[x][y];

    int neighbors[NEIGHBORS][2] = {{x - 1, y}, {x - 1, y - 1}, {x - 1, y + 1}, {x + 1, y}, {x + 1, y - 1}, {x + 1, y + 1}, {x, y - 1}, {x, y + 1}};

    int neighbors_num = 0;
    int same_neighbors = 0;

    for (int i = 0; i < NEIGHBORS; i++) {
        int coords_x = neighbors[i][0];
        int coords_y = neighbors[i][1];

        if (!(coords_x >= size) && !(coords_x < 0) && !(coords_y >= size) && !(coords_y < 0)) {
            
            char coord_char = board[coords_x][coords_y];
            if (coord_char == type) {
                same_neighbors += 1;
            }

            if (coord_char != VACANT) {
                neighbors_num += 1;
            }
        }
    }

    float percentage;
    if (neighbors_num > 0) {
        percentage = ((float)same_neighbors / (float)neighbors_num) * 100;
    } else {
        percentage = 100;
    }

    // printf("%f %d %d %d %d %c\n", percentage, same_neighbors, neighbors_num, x, y, type);

    if (percentage >= strength) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/// only used for the initial state 0 cycle
float calculate_total_happiness(int size, char board[][MAX_SIZE], int happiness_strength) {
    int num_happy = 0;
    int num_sad = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char char_at = board[i][j];
            if (char_at != VACANT) {
                if (is_happy(happiness_strength, i, j, size, board)) {
                    num_happy += 1;
                } else {
                    num_sad += 1;
                }
            }
        }
    }

    return ((float)num_happy) / ((float)(num_happy + num_sad));
}

/// updates the board state with the given happiness strength. also sets the moves_cycle and happiness_cycle pointers
void update_board(int size, char board[][MAX_SIZE], int happiness_strength, int *moves_cycle, float *happiness_cycle) {
    int vacant_positions[MAX_LINEAR_SIZE][2];
    int num_vacant_positions = 0;

    int unhappy_coordinates[MAX_LINEAR_SIZE][2];
    int num_unhappy_coordinates = 0;
    int num_happy_coordinates = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char char_at_position = board[i][j];
            if (char_at_position == VACANT) {
                vacant_positions[num_vacant_positions][0] = i;
                vacant_positions[num_vacant_positions][1] = j;

                num_vacant_positions++;
            } else {
                int happy = is_happy(happiness_strength, i, j, size, board);
                if (happy == FALSE) {
                    unhappy_coordinates[num_unhappy_coordinates][0] = i;
                    unhappy_coordinates[num_unhappy_coordinates][1] = j;

                    num_unhappy_coordinates++;
                } else {
                    num_happy_coordinates++;
                }
            }
        }
    }

    int num_moves = num_vacant_positions > num_unhappy_coordinates ? num_unhappy_coordinates : num_vacant_positions;
    for (int i = 0; i < num_moves; i++) {
        char old_char = board[unhappy_coordinates[i][0]][unhappy_coordinates[i][1]];
        board[vacant_positions[i][0]][vacant_positions[i][1]] = old_char;
        board[unhappy_coordinates[i][0]][unhappy_coordinates[i][1]] = VACANT;
    }

    *moves_cycle = num_moves;
    *happiness_cycle = ((float)num_happy_coordinates) / ((float)(num_happy_coordinates + num_unhappy_coordinates));
}

/// creates the board state by filling and randomizing the board
void create_board(int size, char board[][MAX_SIZE], int end_num, int new_num) {
    srand(41);

    char one_d[MAX_LINEAR_SIZE];
    int true_size = size * size;

    int vac_num = (size * size) - (end_num + new_num);
    int current_index = 0;

    for (int i = current_index; i < end_num; i++) {
        one_d[i] = END_LINE;
    }

    current_index = end_num;

    for (int i = current_index; i < end_num + new_num; i++) {
        one_d[i] = NEW_LINE;
    }

    current_index = end_num + new_num;

    for (int i = current_index; i < end_num + new_num + vac_num; i++) {
        one_d[i] = VACANT;
    }

    // do the actual shuffling
    for (int i = 0; i < true_size - 1; i++) {
        int j = rand() % true_size;
        char curr_val = one_d[i];
        one_d[i] = one_d[j];
        one_d[j] = curr_val;
    }

    int k = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = one_d[k++];
        }
    }
}

/// prints the board using printf
void print_board(int size, char board[][MAX_SIZE]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

/// prints the board using print
void print_board_ncurses(int size, char board[][MAX_SIZE]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printw("%c", board[i][j]);
        }
        printw("\n");
    }
}