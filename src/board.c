/// board.c
/// handles all things related to the board state
/// author: tom schollenberger

#include <stdio.h>
#include <stdlib.h>

#include "board.h"

#define TRUE 1
#define FALSE 0
#define NEIGHBORS 8

int is_happy(int strength, int x, int y, int size, char board[][MAX_SIZE]) {
    char type = board[x][y];

    int neighbors[NEIGHBORS][2] = {{x - 1, y}, {x - 1, y - 1}, {x - 1, y + 1}, {x + 1, y}, {x + 1, y - 1}, {x + 1, y + 1}, {x, y - 1}, {x, y + 1}};

    int neighbors_num = 0;
    int same_neighbors = 0;

    for (int i = 0; i < NEIGHBORS; i++) {
        int coords_x = neighbors[i][0];
        int coords_y = neighbors[i][1];

        if (!(coords_x > size) && !(coords_x < 0) && !(coords_y > size) && !(coords_y < 0)) {
            neighbors_num += 1;
            char coord_char = board[coords_y][coords_x];
            if (coord_char == type) {
                same_neighbors += 1;
            } else if (coord_char == '.') {
                neighbors_num -= 1;
            }
        }
    }

    float percentage = ((float)same_neighbors / (float)neighbors_num) * 100;
    if (percentage >= strength) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void clone_board(int size, char board[][MAX_SIZE], char clone[][MAX_SIZE]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            clone[i][j] = board[i][j];
        }
    }
}

int update_board(int size, char board[][MAX_SIZE], int happiness_strength) {
    char clone[MAX_SIZE][MAX_SIZE];
    clone_board(size, board, clone);

    int vacant_positions[MAX_LINEAR_SIZE][2];
    int num_vacant_positions = 0;

    int unhappy_coordinates[MAX_LINEAR_SIZE][2];
    int num_unhappy_coordinates = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char char_at_position = board[i][j];
            if (char_at_position == '.') {
                vacant_positions[num_vacant_positions][0] = i;
                vacant_positions[num_vacant_positions][1] = j;

                num_vacant_positions++;
            } else {
                int happy = is_happy(happiness_strength, j, i, size, board);
                if (happy == FALSE) {
                    unhappy_coordinates[num_unhappy_coordinates][0] = i;
                    unhappy_coordinates[num_unhappy_coordinates][1] = j;

                    num_unhappy_coordinates++;
                }
            }
        }
    }

    int num_moves = 0;

    return num_moves;
}

void fill_board(int size, char board[][MAX_SIZE], int amount, char fill_char) {
    for (int i = 0; i < amount; i++) {
        int row = rand();
        row %= size;
        int col = rand();
        col %= size;
        if (board[row][col] == '.') {
            board[row][col] = fill_char;
        } else {
            i--;
        }
    }
}

void create_board(char board[][MAX_SIZE], int dimension, int end_num, int new_num) {
    // int size = dimension * dimension;
    // printf("%d\n", size);
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            board[i][j] = '.';
        }
    }

    fill_board(dimension, board, end_num, 'e');
    fill_board(dimension, board, new_num, 'n');
}

void print_board(int size, char board[][MAX_SIZE]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}