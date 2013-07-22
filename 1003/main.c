#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    while (1) {
        char *one_line = NULL;
        size_t len_line = 0;
        size_t ret_line = 0;
        int a, b;
        char buffer[1024];
        int i = 0;
        int j = 0;

        ret_line = getline(&one_line, &len_line, stdin);
        if (ret_line == -1 || one_line[0] == '\n')
            exit(0);
        for (i = 0; i < len_line; i++) {
            if (one_line[i] != ',')
                buffer[j++] = one_line[i];
        }
        sscanf(buffer, "%d %d\n", &a, &b);
        printf("%d\n", a + b);
    }
    return 0;
}
