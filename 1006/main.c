#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    while (1) {
        char *one_line = NULL;
        size_t len_line = 0, ret_line = 0;
        int ac = 0;

        ret_line = getline(&one_line, &len_line, stdin);
        if (ret_line == -1 || one_line[0] == '\n')
            exit(0);

        // validation check
        int i = 0;
        for (; i < (ret_line - 1); i++) {
            if (one_line[i] != 'z' && one_line[i] != 'o' && one_line[i] != 'j')
                goto print;
        }


        char *pos_z = strchr(one_line, 'z');
        if (pos_z == NULL ||
            (pos_z != NULL && strchr(pos_z + 1, 'z') != NULL))
            goto print;
        char *pos_j = strchr(one_line, 'j');
        if (pos_j == NULL ||
            pos_j < pos_z ||
            (pos_j != NULL && strchr(pos_j + 1, 'j') != NULL))
            goto print;
        int a = pos_z - one_line;
        int b = pos_j - pos_z - 1;
        int c = ret_line - 1 - (pos_j - one_line + 1);

        free(one_line);
        while (a >= 0 && b >= 0 && c >= 0) {
            if (a == c && b == 1) {
                ac = 1;
                break;
            } else {
                b = b - 1;
                c = c - a;
            }
        }

print:
        if (ac)
            printf("Accepted\n");
        else
            printf("Wrong Answer\n");
    }
    return 0;
}
