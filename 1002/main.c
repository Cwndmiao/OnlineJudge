#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool inline within_tolerance(int a, int b, int t) {
    int max = a > b? a : b;
    int min = a + b - max;
    return (max - min) <= t;
}

int main(int argc, char **argv) {
    while (1) {
        int full_score = 0;
        int tolerance = 0;
        int grade_1 = 0;
        int grade_2 = 0;
        int grade_3 = 0;
        int grade_judge = 0;
        double final_score = 0.0;

        char* one_line = NULL;
        size_t len_line = 0;
        size_t size_line = 0;
        size_line = getline(&one_line, &len_line, stdin);
        if (size_line == -1 || one_line[0] == '\n')
            exit(0);
        sscanf(one_line, "%d %d %d %d %d %d\n", &full_score, &tolerance, &grade_1, &grade_2, &grade_3, &grade_judge);
        if (within_tolerance(grade_1, grade_2, tolerance)) {
            final_score = (double)(grade_1 + grade_2) / (double)2;
        } else {
            bool t1 = within_tolerance(grade_1, grade_3, tolerance);
            bool t2 = within_tolerance(grade_2, grade_3, tolerance);
            
            if (t1 && t2)
                final_score = (double)(grade_3 > ((grade_1 > grade_2) ? grade_1 : grade_2) ? grade_3 : ((grade_1 > grade_2) ? grade_1 : grade_2));
            else if (!t1 && !t2)
                final_score = (double)grade_judge;
            else {
                int d1 = (grade_1 > grade_3) ? (grade_1 - grade_3) : (grade_3 - grade_1);
                int d2 = (grade_2 > grade_3) ? (grade_2 - grade_3) : (grade_3 - grade_2);
                if (d1 < d2) {
                    final_score = (double)(grade_1 + grade_3) / (double)2;
                } else {
                    final_score = (double)(grade_2 + grade_3) / (double)2;
                }
            }
        }
        printf("%.1f\n", final_score);
        free(one_line);
    }
    return 0;
}
