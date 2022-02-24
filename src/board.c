/// board.c
/// handles all things related to the board state
/// author: tom schollenberger

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "board.h"

#define _DEFAULT_SOURCE

#define TRUE 1
#define FALSE 0
#define NEIGHBORS 8
#define VACANT '.'
#define END_LINE 'e'
#define NEW_LINE 'n'

/**
 * @private Should only be called internally
 * @brief Checks if a given coordinate is happy
 * 
 * @param happiness_strength The threshold that determines if a character is happy. An int 0-100
 * @param x The x coordinate of the desired spot to check
 * @param y The y coordinate of the desired spot to check
 * @param size The actual size of the underlying board
 * @param board The 2D character MAX_SIZE x MAX_SIZE board
 * @return int Returns 1 if happy, 0 if not happy.
 * #define TRUE and #define FALSE are used to represent these
 */
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
    *happiness_cycle = ((float)num_happy_coordinates) / ((float)(num_happy_coordinates + num_vacant_positions));
}

void fill_board(int size, char board[][MAX_SIZE], int amount, char fill_char) {
    srandom(time(NULL));

    for (int i = 0; i < amount; i++) {
        int row = random();
        row %= size;
        int col = random();
        col %= size;
        if (board[row][col] == VACANT) {
            board[row][col] = fill_char;
        } else {
            i--;
        }
    }
}

void create_board(int size, char board[][MAX_SIZE], int end_num, int new_num) {
    // printf("%d\n", size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = VACANT;
        }
    }

    fill_board(size, board, end_num, END_LINE);
    fill_board(size, board, new_num, NEW_LINE);
}

void print_board(int size, char board[][MAX_SIZE]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

void print_board_ncurses(int size, char board[][MAX_SIZE]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printw("%c", board[i][j]);
        }
        printw("\n");
    }
}