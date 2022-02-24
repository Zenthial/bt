#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "options.h"

static const char USAGE_MESSAGE[] = "usage:\nbracetopia [-h] [-t N] [-c N] [-d dim] [-s %%str] [-v %%vac] [-e %%end]";
static const char LINE_ONE[] = "Option      Default   Example   Description";
static const char LINE_TWO[] = "'-h'        NA        -h        print this usage message.";
static const char LINE_THREE[] = "'-t N'      900000    -t 5000   microseconds cycle delay.";
static const char LINE_FOUR[] = "'-c N'      NA        -c4       count cycle maximum value.";
static const char LINE_FIVE[] = "'-d dim'    15        -d 7      width and height dimension.";
static const char LINE_SIX[] = "'-s %str'   50        -s 30     strength of preference.";
static const char LINE_SEVEN[] = "'-v %vac'   20        -v30      percent vacancies.";
static const char LINE_EIGHT[] = "'-e %endl'  60        -e75      percent Endline braces. Others want Newline.";

int get_options(int argc, char *argv[], int *dimension, int *strength, int *vacancy_percentage, int *endline_percentage, int *print_cycle_count, int *delay) {
    int opt;

    if (argc == 0) {
        fprintf(stderr, USAGE_MESSAGE);
        return(EXIT_FAILURE);
    }

    while ((opt = getopt(argc, argv, "hd:v:s:e:c:t:")) != -1) {
        switch ( opt ) {
            case 'h':
                printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", USAGE_MESSAGE, LINE_ONE, LINE_TWO, LINE_THREE, 
                    LINE_FOUR, LINE_FIVE, LINE_SIX, LINE_SEVEN, LINE_EIGHT
                );
                break;
            case 'd': // handle dimension setting
                *dimension = (int)strtol(optarg, NULL, 10);
                if (*dimension < 5) { // min size is 5
                    *dimension = 5;
                } else if (*dimension > 39) { // max size is 39
                    *dimension = 39;
                }
                
                break;
            case 's': // handle dimension setting
                *strength = (int)strtol(optarg, NULL, 10);
                if (*strength < 0) { // min size is 5
                    *strength = 0;
                } else if (*strength > 100) { // max size is 39
                    *strength = 100;
                }
                
                break;
            case 'v': // handle dimension setting
                *vacancy_percentage = (int)strtol(optarg, NULL, 10);
                if (*vacancy_percentage < 0) { // min size is 5
                    *vacancy_percentage = 0;
                } else if (*vacancy_percentage > 100) { // max size is 39
                    *vacancy_percentage = 100;
                }
                
                break;
            case 'e': // handle dimension setting
                *endline_percentage = (int)strtol(optarg, NULL, 10);
                if (*endline_percentage < 0) { // min size is 5
                    *endline_percentage = 0;
                } else if (*endline_percentage > 100) { // max size is 39
                    *endline_percentage = 100;
                }

                break;
            case 'c': // handle dimension setting
                *print_cycle_count = (int)strtol(optarg, NULL, 10);

                break;
            case 't':
                if ((int)strtol(optarg, NULL, 10) > 0) {
                    *delay = (int)strtol(optarg, NULL, 10);
                }
                break;
            default:
                // some unknown, possibly unacceptable option flag
                fprintf(stderr, USAGE_MESSAGE);
                return (EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}