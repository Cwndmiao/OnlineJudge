#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_digit(int i) {
    return ((i >= '0') && (i <= '9'));
}


int main(int argc, char **argv) {
    int input_array[100];
    int input_index = 0;
    int input_tmp = 0;
    int i = 0;

    while ((input_tmp = fgetc(stdin)) != EOF) {
        if (is_digit(input_tmp))
            input_array[input_index++] = input_tmp - '0';
    }

    for (i = 0; i < input_index / 2; i++) {
        int output = input_array[2 * i] + input_array[2 * i + 1];
        printf("%d\n", output);
    }
    return 0;
}
