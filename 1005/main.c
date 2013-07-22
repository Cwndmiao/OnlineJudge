#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHOICES 10
#define MAX_SCHOOLS 20
#define MAX_STUDENTS 100

struct student_info {
    int grade_entrance;
    int grade_interview;
    int final_score;
    int choices[MAX_CHOICES];
    int id;
};

struct school_info {
    int school_plan;
    int cur;
    int admitted_students[10];
    int last_final_grade;
    int last_entrance_grade;
};

int student_compare(const void *a, const void *b) {
    const struct student_info *stu1 = (const struct student_info*)a;
    const struct student_info *stu2 = (const struct student_info*)b;
    if (stu1->final_score < stu2->final_score)
        return 1;
    else if (stu1->final_score > stu2->final_score)
        return -1;
    else {
        if (stu1->grade_entrance < stu2->grade_entrance)
            return 1;
        else if (stu1->grade_entrance > stu2->grade_entrance)
            return -1;
        else
            return 0;
    }
}

int int_compare(const void *a, const void *b) {
    int id1 = *(const int*)a; 
    int id2 = *(const int*)b;
    if (id1 < id2)
        return -1;
    else
        return 1;
}

int main(int argc, char **argv) {
    while (1) {
        int num_of_students = 0;
        int num_of_schools = 0;
        int num_of_choices = 0;
        char* one_line = NULL;
        size_t len_line = 0;
        size_t ret_line = 0;
        struct school_info school_infos[MAX_SCHOOLS];
        int i = 0;
        int j = 0;
        int cur = 0;
        struct student_info student_infos[MAX_STUDENTS];
        
        // do init
        memset((void*)&school_infos, 0, sizeof(school_infos));
        memset((void*)&student_infos, 0, sizeof(student_infos));

        // read meta information
        ret_line = getline(&one_line, &len_line, stdin);
        if (ret_line == -1 || one_line[0] == '\n')
            exit(0);
        sscanf(one_line, "%d %d %d\n", &num_of_students, &num_of_schools, &num_of_choices);
        free(one_line);

        // read school plan
        one_line = NULL;
        len_line = 0;
        ret_line = getline(&one_line, &len_line, stdin);
        for (i = 0, j = 0; i < ret_line; i++) {
            if (one_line[i] == ' ' || one_line[i] == '\n') {
                sscanf(&one_line[j], "%d", &school_infos[cur++].school_plan);
                j = i + 1;
            }
        }
        free(one_line);

        // read student info
        for (i = 0; i < num_of_students; i++) {
            char *choice = NULL;
            one_line = NULL;
            len_line = 0;
            ret_line = getline(&one_line, &len_line, stdin);
            sscanf(one_line, "%d %d", &student_infos[i].grade_entrance, &student_infos[i].grade_interview);
            student_infos[i].final_score = (student_infos[i].grade_entrance + student_infos[i].grade_interview) / 2;
            strtok(one_line, " ");
            strtok(NULL, " ");
            cur = 0;
            while ((choice = strtok(NULL, " ")) != NULL)
                sscanf(choice, "%d", &student_infos[i].choices[cur++]);
            student_infos[i].id = i;
        }

        // sorting
        qsort((void*)student_infos, num_of_students, sizeof(struct student_info), &student_compare);     

        // admitting progress
        for (i = 0; i < num_of_students; i++) {
            for (j = 0; j < num_of_choices; j++) {
                int school_index = student_infos[i].choices[j];
                
                if (school_infos[school_index].cur < school_infos[school_index].school_plan) {
                    school_infos[school_index].admitted_students[school_infos[school_index].cur++] = student_infos[i].id;
                    school_infos[school_index].last_final_grade = student_infos[i].final_score;
                    school_infos[school_index].last_entrance_grade = student_infos[i].grade_entrance;
                    break;
                }
                if (student_infos[i].final_score == school_infos[school_index].last_final_grade 
                        && student_infos[i].grade_entrance == school_infos[school_index].last_entrance_grade) {
                    school_infos[school_index].admitted_students[school_infos[school_index].cur++] = student_infos[i].id;
                    break;
                }
            } 
        }

        // final sorting
        for (i = 0; i < num_of_schools; i++) {
            qsort((void*)school_infos[i].admitted_students, school_infos[i].cur, sizeof(int), &int_compare);
        }
        
        // print results
        for (i = 0; i < num_of_schools; i++) {
            if (school_infos[i].cur > 0) {
                for (j = 0; j < school_infos[i].cur - 1; j++) {
                    printf("%d ", school_infos[i].admitted_students[j]);
                }
                printf("%d\n", school_infos[i].admitted_students[j]);
            } else
                printf("\n");
        }
    }

    return 0;
}
