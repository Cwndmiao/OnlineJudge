#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char inline max(char a, char b) {
    return (a > b) ? a : b;
}

char inline min(char a, char b) {
    return (a < b) ? a : b;
}

void replace(int len, char array[len], char from, char to) {
    int i = 0;
    for (; i < len; i++) {
        if (array[i] == from)
            array[i] = to;
    }
    return;
}

int main(int argc, char **argv) {
    while (1) {
        char *one_line = NULL;
        size_t len_line = 0, ret_line = 0;
        int num_of_people = 0;
        int num_of_relationship = 0;
        char *data = NULL;
        int groups = 0;
        int watermark = 0;

        ret_line = getline(&one_line, &len_line, stdin);
        if (one_line[0] == '0')
            exit(0);
        sscanf(one_line, "%d %d\n", &num_of_people, &num_of_relationship);
        free(one_line);
        data = (char*)malloc(sizeof(char) * num_of_people);
        if (data == NULL)
            exit(-1);
        memset((void*)data, -1, sizeof(char) * num_of_people);

        int i = 0;
        for (; i < num_of_relationship; i++) {
            int a = 0;
            int b = 0;
            one_line = NULL;
            len_line = ret_line = 0;
            ret_line = getline(&one_line, &len_line, stdin);
            sscanf(one_line, "%d %d\n", &a, &b);
            free(one_line);

            if (data[a - 1] == -1 && data[b - 1] == -1) {
                data[a -1] = data[b - 1] = watermark++;
                groups++;
            } else if (data[a - 1] == -1)
                data[a - 1] = data[b - 1];
            else if (data[b - 1] == -1)
                data[b - 1] = data[a - 1]; 
            else if (data[a - 1] != data[b - 1]) {
                replace(num_of_people, data, max(data[a - 1], data[b - 1]), min(data[a - 1], data[b - 1]));
                groups--;
            }
        }

        // for debug
        //printf("%d %d\n", watermark, groups);
        printf("%d\n", groups);
        free(data);
    }
    return 0;
}
