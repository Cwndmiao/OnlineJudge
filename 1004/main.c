#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    while (1) {
        int *first_array = NULL, *second_array = NULL; 
        int first_len = 0, second_len = 0;
        int first_cur = 0, second_cur = 0;
        char *one_line = NULL;
        size_t len_line = 0;
        size_t ret_line = 0;
        int i = 0;

        ret_line = getline(&one_line, &len_line, stdin);
        if (ret_line == -1 || one_line[0] == '\n')
            exit(0);
        sscanf(one_line, "%d ", &first_len);
        first_array = (int*)malloc(sizeof(int) * first_len);
        for (i = 0; i < ret_line; i++) {
            if (one_line[i] == ' ')
                sscanf(&one_line[i + 1], "%d", &first_array[first_cur++]);
        }
        if (first_cur != first_len) {
            printf("not enough int\n");
            exit(-1);
        }
        free(one_line);

        one_line = NULL;
        len_line = 0;
        ret_line = getline(&one_line, &len_line, stdin);
        sscanf(one_line, "%d ", &second_len);
        second_array = (int*)malloc(sizeof(int) * second_len);
        for (i = 0; i < ret_line; i++) {
            if (one_line[i] == ' ')
                sscanf(&one_line[i + 1], "%d", &second_array[second_cur++]);
        }
        if (second_cur != second_len) {
            printf("not enough int\n");
            exit(-1);
        }
        free(one_line);

        int mid_index = (first_len + second_len - 1) / 2;
        first_cur = 0;
        second_cur = 0;
        i = 0;
        while (i < mid_index) {
            if (first_cur == first_len) {
                second_cur++;
                if (i == (mid_index - 1)) {
                    printf("%d\n", second_array[second_cur]);
                    goto done;
                }
            } else if (second_cur == second_len) {
                first_cur++;
                if (i == (mid_index - 1)) {
                    printf("%d\n", first_array[first_cur]);
                    goto done;
                }
            } else {
                if (first_array[first_cur] < second_array[second_cur]) {
                    first_cur++;
                } else
                    second_cur++;
            }
            i++;
        }
        if (first_cur == first_len)
            printf("%d\n", second_array[second_cur]);
        else if (second_cur == second_len)
            printf("%d\n", first_array[first_cur]);
        else
            printf("%d\n", (first_array[first_cur] < second_array[second_cur]) ? first_array[first_cur] : second_array[second_cur]);

done:
        free(first_array);
        free(second_array);
    }
    return 0;
}
