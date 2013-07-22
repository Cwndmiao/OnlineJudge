#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_palindromic(const char *start, const char *end) {
    while (start < end)
        if (*(start++) != *(end--))
            return false;
    return true;
}

// y x x y
int first_round(char *str, size_t len) {
    int left, left_start, right, max_len = 0;
    for (left_start = 0; left_start < len - 1; left_start++) {
        int cur_len = 0;
        left = left_start;
        right = left + 1;
        while (left >= 0 && right < len && str[left--] == str[right++])
            cur_len += 2;
        if (cur_len > max_len)
            max_len = cur_len;
    }
    return max_len;
}

// a b c b a
int second_round(char *str, size_t len) {
    int left, left_start, right, max_len = 1;
    for (left_start = 0; left_start < len - 2; left_start++) {
        int cur_len = 1;
        left = left_start;
        right = left + 2;
        while (left >= 0 && right < len && str[left--] == str[right++])
            cur_len += 2;
        if (cur_len > max_len)
            max_len = cur_len;
    }
    return max_len;
}



int main(int argc, char **argv) {
    while (1) {
        char *one_line = NULL;
        size_t len_line = 0;
        size_t ret_line = 0;
        int max_len = 0;
        int first = 0, second = 0;
        ret_line = getline(&one_line, &len_line, stdin);
        if (ret_line == -1 || one_line[0] == '\n')
            exit(0);

        first = first_round(one_line, ret_line);
        second = second_round(one_line, ret_line);
        max_len = (first > second) ? first : second;

        printf("%d\n", max_len);
        free(one_line);
    }
    return 0;
}
