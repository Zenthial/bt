#ifndef _BOARD_H_
#define _BOARD_H_

#define MAX_SIZE 39
#define MAX_LINEAR_SIZE 1521 // 39 * 39

void print_board(int size, char board[][MAX_SIZE]);

int update_board(int size, char board[][MAX_SIZE], int happiness_strength);

void create_board(char board[][MAX_SIZE], int dimension, int end_num, int new_num);

#endif // !_BOARD_H_