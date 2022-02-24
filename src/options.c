#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "options.h"


int get_options(int argc, char *argv[], int *dimension, int *strength, int *vacancy_percentage, int *endline_percentage, int *print_cycle_count, int *delay) {
    char USAGE_MESSAGE[] = "usage:\nbracetopia [-h] [-t N] [-c N] [-d dim] [-s %str] [-v %vac] [-e %end]";
    char LINE_ONE[] = "Option      Default   Example   Description";
    char LINE_TWO[] = "'-h'        NA        -h        print this usage message.";
    char LINE_THREE[] = "'-t N'      900000    -t 5000   microseconds cycle delay.";
    char LINE_FOUR[] = "'-c N'      NA        -c4       count cycle maximum value.";
    char LINE_FIVE[] = "'-d dim'    15        -d 7      width and height dimension.";
    char LINE_SIX[] = "'-s %str'   50        -s 30     strength of preference.";
    char LINE_SEVEN[] = "'-v %vac'   20        -v30      percent vacancies.";
    char LINE_EIGHT[] = "'-e %endl'  60        -e75      percent Endline braces. Others want Newline.";
    
    int opt;
    char *leftover;

    if (argc == 0) {
        fprintf(stderr, "%s", USAGE_MESSAGE);
        return(EXIT_FAILURE);
    }

    while ((opt = getopt(argc, argv, "hd:v:s:e:c:t:")) != -1) {
        switch ( opt ) {
            case 'h':
                fprintf(stderr, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", USAGE_MESSAGE, LINE_ONE, LINE_TWO, LINE_THREE, 
                    LINE_FOUR, LINE_FIVE, LINE_SIX, LINE_SEVEN, LINE_EIGHT
                );
                return -1;
                break;
            case 'd': // handle dimension setting
                *dimension = (int)strtol(optarg, &leftover, 10);
                if (*dimension < 5 || *dimension > 39 || strlen(leftover) > 0) { // min size is 5
                    fprintf(stderr, "dimension (%d) must be a value in [5...39]\n", *dimension);
                    fprintf(stderr, "%s", USAGE_MESSAGE);
                    return (EXIT_FAILURE);
                }
                
                break;
            case 's': // handle dimension setting
                *strength = (int)strtol(optarg, &leftover, 10);
                if (*strength <= 0 || *strength >= 100 || strlen(leftover) > 0) { // min size is 5
                    fprintf(stderr, "%s", USAGE_MESSAGE);
                    return (EXIT_FAILURE);
                }
                
                break;
            case 'v': // handle dimension setting
                *vacancy_percentage = (int)strtol(optarg, &leftover, 10);
                if (*vacancy_percentage <= 0 || *vacancy_percentage >= 100 || strlen(leftover) > 0) { // min size is 5
                    // some unknown, possibly unacceptable option flag
                    fprintf(stderr, "%s", USAGE_MESSAGE);
                    return (EXIT_FAILURE);
                }
                
                break;
            case 'e': // handle dimension setting
                *endline_percentage = (int)strtol(optarg, &leftover, 10);
                if (*endline_percentage <= 0 || *endline_percentage >= 100 || strlen(leftover) > 0) { // min size is 5
                    fprintf(stderr, "%s", USAGE_MESSAGE);
                    return (EXIT_FAILURE);
                }

                break;
            case 'c':
                *print_cycle_count = (int)strtol(optarg, &leftover, 10);

                if (*print_cycle_count < 0 || strlen(leftover) > 0) {
                    fprintf(stderr, "%s", USAGE_MESSAGE);
                    return (EXIT_FAILURE);
                }
                break;
            case 't':
                *delay = (int)strtol(optarg, &leftover, 10);

                if (strlen(leftover) > 0 || *delay <= 0) {
                    fprintf(stderr, "%s", USAGE_MESSAGE);
                    return (EXIT_FAILURE);
                }
                break;
            default:
                // some unknown, possibly unacceptable option flag
                fprintf(stderr, "%s", USAGE_MESSAGE);
                return (EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}