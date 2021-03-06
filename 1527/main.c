#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long inline max(long long a, long long b) {
    return (a > b) ? a : b;
}

long long inline min(long long a, long long b) {
    return (a < b) ? a : b;
}

long long first_round(int size, int array[size]) {
    //int sum[size];
    long long *sum = (long long*)malloc(sizeof(long long) * size);
    int i;
    long long max_sum = array[0];
    sum[0] = array[0];

    for (i = 1; i < size; i++) {
        sum[i] = max(sum[i - 1] + array[i], array[i]);
        if (sum[i] > max_sum)
            max_sum = sum[i];
    }
    free(sum);
    return max_sum;
}

/*
int second_round(int size, int array[size], int tmp[][size]) {
    //int tmp[size][size];
    int i = 0;
    int j = 0;
    int max_sum = 0;
    tmp[0][0] = 0;

    for (i = 1; i < size; i++)
        tmp[i][0] = tmp[i - 1][0] + array[i - 1];
    for (j = 1; j < size; j++)
        tmp[0][j] = tmp[0][j - 1] + array[size - j];

    for (i = 1; i < size; i++) {
        for (j = 1; j < (size - i); j++) {
            tmp[i][j] = tmp[i -1][j] + array[i - 1];
            if (tmp[i][j] > max_sum)
                max_sum = tmp[i][j];
        }
    }
    return max_sum;
}
*/

long long second_round(int size, int array[size]) {
    //int sum[size];
    long long *sum = (long long*)malloc(sizeof(long long) * size);
    int i;
    long long min_sum = array[0];
    long long max_sum = 0;
    sum[0] = array[0];

    for (i = 1; i < size; i++) {
        sum[i] = min(sum[i - 1] + array[i], array[i]);
        if (sum[i] < min_sum)
            min_sum = sum[i];
    }

    for (i = 0; i < size; i++) {
        max_sum += array[i];
    }
    max_sum -= min_sum;
    free(sum);
    return max_sum;
}

int main(int argc, char **argv) {
    while (1) {
        char *one_line = NULL;
        size_t len_line = 0, ret_line = 0;
        int *array = NULL;
        int array_len = 0;
        char *p = NULL;
        int cur = 0;
        long long first = 0;
        long long second = 0;
        long long max_sum = 0;
        //void *tmp = NULL;

        ret_line = getline(&one_line, &len_line, stdin);
        if (ret_line == -1 || one_line[0] == '\n')
            exit(0);
        sscanf(one_line, "%d\n", &array_len);
        free(one_line);
        array = (int*)malloc(sizeof(int) * array_len);
        //tmp = (void*)malloc(sizeof(int) * array_len * array_len);

        one_line = NULL;
        len_line = 0;
        getline(&one_line, &len_line, stdin);
        array[cur++] = atoi(one_line);
        for (p = strtok(one_line, " "); (p = strtok(NULL, " ")) != NULL;) {
            array[cur++] = atoi(p);
        }
        free(one_line);

        // first round
        first = first_round(array_len, array);
        // second round
        // however "Memory Limit Exceeds" happens according the OnlineJudge
        second = second_round(array_len, array/*, (int(*)[array_len])tmp*/);
        max_sum = max(first, second); 
        printf("%lld\n", max_sum);
        free(array);
        //free(tmp);
    }
    return 0;
}
