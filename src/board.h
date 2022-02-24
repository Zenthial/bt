#ifndef _BOARD_H_
#define _BOARD_H_

#define MAX_SIZE 39
#define MAX_LINEAR_SIZE 1521 // 39 * 39

/**
 * @brief Prints out the given board when in an ncurses screen. Should not be used while in ncurses mode
 * 
 * @param size The actual size of the underlying board
 * @param board The 2D character MAX_SIZE x MAX_SIZE board
 */
void print_board(int size, char board[][MAX_SIZE]);

/**
 * @brief Prints out the given board when in an ncurses screen. Replaces printf with printw
 * 
 * @param size The actual size of the underlying board
 * @param board The 2D character MAX_SIZE x MAX_SIZE board
 */
void print_board_ncurses(int size, char board[][MAX_SIZE]);

/**
 * @brief Updates the given board based off of the given happiness strength.
 * Checks each character within the matrix to see if it is happy
 * 
 * @param size The actual size of the underlying board
 * @param board The 2D character MAX_SIZE x MAX_SIZE board
 * @param happiness_strength The threshold that determines if a character is happy. An int 0-100
 * @param moves_cycle Pointer to the moves_this_cycle int
 * @param happiness_cycle Pointer to the happiness this cycle int
 * @return int - The number of updated characters
 */
void update_board(int size, char board[][MAX_SIZE], int happiness_strength, int *moves_cycle, float *happiness_cycle);

/**
 * @brief Create a board object
 * 
 * @param size The actual size of the underlying board to be filled
 * @param board  The 2D character MAX_SIZE x MAX_SIZE board to be filled
 * @param end_num The amount of endline characters to be added into the board
 * @param new_num The amount of newline characters to be added into the board
 */
void create_board(int size, char board[][MAX_SIZE], int end_num, int new_num);

#endif // !_BOARD_H_