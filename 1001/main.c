#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_metrics(int *r, int *c) {
    char *one_line = NULL;
    size_t len_line = 100;
    getline(&one_line, &len_line, stdin);
    if (atoi(one_line) == 0)
        exit(0);
    sscanf(one_line, "%d %d", r, c);
    free(one_line);
    return;
}

int* get_matrix(int r, int c) {
    int* p = (int*)malloc(sizeof(int) * r * c);
    int cur_r = 0;
    for (cur_r = 0; cur_r < r; cur_r++) {
        /*
        if (c == 2) {
            char *one_line = NULL;
            size_t len_line = 100;
            getline(&one_line, &len_line, stdin);
            sscanf(one_line, "%d %d\n", &p[cur_r * c], &p[cur_r * c + 1]);
            free(one_line);
        } else if (c == 3){
            char *one_line = NULL;
            size_t len_line = 100;
            getline(&one_line, &len_line, stdin);
            sscanf(one_line, "%d %d %d\n", &p[cur_r * c], &p[cur_r * c + 1], &p[cur_r * c + 2]);
            free(one_line);
        } else {
            printf("column is not 2 or 3\n");
            exit(-1);
        }
        */
        char *one_line = NULL;
        size_t len_line = 1024;
        int i_line = 0;
        int last_i_line = 0;
        int index = 0;
        
        getline(&one_line, &len_line, stdin);
        for (; i_line < len_line; i_line++) {
            if (one_line[i_line] == ' ' || one_line[i_line] == '\n') {
                one_line[i_line] = '\0';
                p[cur_r * c + index] = atoi(&one_line[last_i_line]);
                index++;
                last_i_line = i_line + 1;
            }
        }
        if (index != c) {
            printf("less than %d elements in one row\n", c);
            exit(-1);
        }
        free(one_line);
    }
    return p;
}

void add_matrix(int *p, int* q, int r, int c) {
    int i = 0;
    for (; i < r * c; ++i) {
        p[i] += q[i];
    }
    return;
}

int zero_lines(int* p, int r, int c) {
    int ret = 0;
    // check rows
    int r_index = 0;
    for (; r_index < r; r_index++) {
        int c_index = 0;
        for (; c_index < c; c_index++) {
            if (p[r_index * c + c_index] != 0)
                break;
        }
        if (c_index == c)
            ret++;
    }
    // check columns
    int c_index = 0;
    for (; c_index < c; c_index++) {
        int r_index = 0;
        for (; r_index < r; r_index++) {
            if (p[r_index * c + c_index] != 0)
                break;
        }
        if (r_index == r)
            ret++;
    }
    return ret;
}

int main(int argc, char **argv) {
    while (1) {
        int row, column;
        int *m, *n;
        int zeros;
        get_metrics(&row, &column);
        //printf("%d %d\n", row, column);
        m = get_matrix(row, column);
        n = get_matrix(row, column);
        add_matrix(m, n, row, column);
        zeros = zero_lines(m, row, column);
        printf("%d\n", zeros);
        free(m);
        free(n);
    }
    return 0;
}
