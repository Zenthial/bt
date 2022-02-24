#ifndef _OUTPUT_CYCLES_H_
#define _OUTPUT_CYCLES_H_

/**
 * @brief Handles the printing for ncurses mode
 * 
 * @param size The actual size of the underlying board to be filled
 * @param board  The 2D character MAX_SIZE x MAX_SIZE board to be filled
 * @param happiness_strength The threshold that determines if a character is happy. An int 0-100
 * @param end_percent The percentage of endlines
 * @param vacancy_percent The percentage of vacant spots
 * @param delay The millisecond delay between refreshes
 */
void handle_infinite_cycle(int size, char board[][MAX_SIZE], int happiness_strength, int end_percent, int vacancy_percent, int delay);

/**
 * @brief Handles the finite print cycle
 * 
 * @param num_cycles Amount of cycles to print
 * @param size The actual size of the underlying board to be filled
 * @param board  The 2D character MAX_SIZE x MAX_SIZE board to be filled
 * @param happiness_strength The threshold that determines if a character is happy. An int 0-100
 * @param end_percent The percentage of endlines
 * @param vacancy_percent The percentage of vacant spots
 */
void handle_print_cycle(int num_cycles, int size, char board[][MAX_SIZE], int happiness_strength, int end_percent, int vacancy_percent);

#endif