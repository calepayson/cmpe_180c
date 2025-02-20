#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int min;
    int max;
} Range;

typedef struct {
    int value;
    bool required;
    bool provided;
    Range range;
    char *name;
} Input;

const Range NUMS_TO_GEN_RANGE = {1, 32767};
const Range NUMS_RANGE = {1, 32767};
const Range POWER_BALL_RANGE = {1, 32767};
const Range NUM_SETS_RANGE = {1, 32767};

void validate_input(Input *input);

int rand_in_range(int min, int max);

bool num_in_arr(int arr[], int size, int num);

int main(int argc, char *argv[]) {
    Input numbers_to_generate = {0, true, false, NUMS_TO_GEN_RANGE,
                                 "-n <NumbersToGenerate>"};
    Input max_number = {0, true, false, NUMS_RANGE, "-r <MaxNumber>"};
    Input max_power_ball_number = {0, false, false, POWER_BALL_RANGE,
                                   "-p <MaxPowerBallNumber"};
    Input number_sets_to_generate = {1, false, false, NUM_SETS_RANGE,
                                     "-N <NumberSetsToGenerate"};

    // Read in the arguments
    int opt;
    while ((opt = getopt(argc, argv, "n:r:p:N:")) != -1) {
        switch (opt) {
            case 'n':
                numbers_to_generate.value = atoi(optarg);
                numbers_to_generate.provided = true;
                break;
            case 'N':
                number_sets_to_generate.value = atoi(optarg);
                number_sets_to_generate.provided = true;
                break;
            case 'p':
                max_power_ball_number.value = atoi(optarg);
                max_power_ball_number.provided = true;
                break;
            case 'r':
                max_number.value = atoi(optarg);
                max_number.provided = true;
                break;
            default:
                fprintf(stderr,
                        "Usage: %s -n <NumbersToGenerate> -r <MaxNumber> [-p "
                        "<MaxPowerBallNumber>] [-N <NumberSetsToGenerate>]",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    validate_input(&numbers_to_generate);
    validate_input(&max_number);
    validate_input(&max_power_ball_number);
    validate_input(&number_sets_to_generate);

    if (numbers_to_generate.value > max_number.value) {
        fprintf(stderr,
                "-n <NumbersToGenerate> must be less than or equal to "
                "-r <MaxNumber>.\n"
                "    NumbersToGenerate: %i\n"
                "    MaxNumber: %i\n",
                numbers_to_generate.value, max_number.value);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < number_sets_to_generate.value; i++) {
        int arr[numbers_to_generate.value];
        for (int j = 0; j < numbers_to_generate.value; j++) {
            int num;
            bool duplicate;

            duplicate = true;
            while (duplicate) {
                num = rand_in_range(max_number.range.min, max_number.value);
                duplicate = num_in_arr(arr, j, num);
                arr[j] = num;
            }

            if (!max_power_ball_number.provided &&
                j + 1 == numbers_to_generate.value) {
                printf("%i", num);
            } else {
                printf("%i, ", num);
            }
        }
        if (max_power_ball_number.provided) {
            int num = rand_in_range(max_power_ball_number.range.min,
                                    max_power_ball_number.value);
            printf("%i", num);
        }
        printf("\n");
    }

    return 0;
}

void validate_input(Input *input) {
    if (input->required) {
        if (!input->provided) {
            fprintf(stderr, "You must provide a positive integer for %s.\n",
                    input->name);
            exit(EXIT_FAILURE);
        }
        if (input->value == 0) {
            fprintf(stderr,
                    "Error parsing %s. Please provide a positive integer.\n",
                    input->name);
            exit(EXIT_FAILURE);
        }
    }

    if (input->provided &&
        (input->value < input->range.min || input->value > input->range.max)) {
        fprintf(stderr,
                "%s must be a value within [%i, %i].\n"
                "You provided: %i\n",
                input->name, input->range.min, input->range.max, input->value);
        exit(EXIT_FAILURE);
    }
}

int rand_in_range(int min, int max) { return min + rand() % (max - min + 1); }

bool num_in_arr(int arr[], int size, int num) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == num) {
            return true;
        }
    }
    return false;
}
