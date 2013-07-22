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


int main(int argc, char **argv) {
    while (1) {
        char *one_line = NULL;
        size_t len_line = 0;
        size_t ret_line = 0;
        int max_len = 0;
        ret_line = getline(&one_line, &len_line, stdin);
        if (ret_line == -1 || one_line[0] == '\n')
            exit(0);

        //int i = 0;
        //for (i = 0; i < ret_line; i++) {
        //    int j = i;
        //    for (j = i; j < ret_line; j++) {
        //        if (is_palindromic(one_line + i, one_line + j) &&
        //                (j - i + 1) > max_len)
        //            max_len = j - i + 1;
        //    }
        //}
        for (max_len = ret_line - 1; max_len > 0; max_len--) {
            const char* start = one_line;
            for (; start <= one_line + ret_line - max_len - 1; start++) {
                const char* end = start + max_len - 1;
                if (is_palindromic(start, end))
                    goto done;
            }
        }
done:
        printf("%d\n", max_len);
        free(one_line);
    }
    return 0;
}
