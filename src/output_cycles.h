#ifndef _OUTPUT_CYCLES_H_
#define _OUTPUT_CYCLES_H_

void handle_infinite_cycle(int size, char board[][MAX_SIZE], int happiness_strength, int dimensions, int end_percent, int vacancy_percent, int delay);

void handle_print_cycle(int num_cycles, int size, char board[][MAX_SIZE], int happiness_strength, int dimensions, int end_percent, int vacancy_percent);

#endif