#ifndef _OPTIONS_H_
#define _OPTIONS_H_

/**
 * @brief Parses the command line arguments
 * 
 * @param argc number of command line args
 * @param argv list of command line args
 * @param dimension pointer to the size of the board
 * @param strength pointer to the happiness strength
 * @param vacancy_percentage pointer to the vacancy percentage
 * @param endline_percentage pointer to the endline percentage
 * @param print_cycle_count pointer to the print cycle count
 * @param delay pointer to the ms delay
 * @return int 0 if all command line args are passed correctly, 1 if they failed
 */
int get_options(int argc, char *argv[], int *dimension, int *strength, int *vacancy_percentage, int *endline_percentage, int *print_cycle_count, int *delay);

#endif