#include <stdio.h>
#include "../console.h"
#define STUDENTS 3
#define EXAMS 4

int minimum(const int grades[][EXAMS], int pupils, int tests)
{
    int low = grades[0][0];
    for (int i = 0; i < pupils; ++i) {
        for (int j = 0; j < tests; ++j) {
            if (grades[i][j] < low) {
                low = grades[i][j];
            }
        }
    }
    return low;
}

int maximum(const int grades[][EXAMS], int pupils, int tests)
{
    int high = grades[0][0];
    for (int i = 0; i < pupils; ++i) {
        for (int j = 0; j < tests; ++j) {
            if (grades[i][j] > high) {
                high = grades[i][j];
            }
        }
    }
    return high;
}

double average(const int setOfGrades[], int tests)
{
    int total = 0;
    for (int i = 0; i < tests; ++i) {
        total += setOfGrades[i];
    }
    return (double)total / tests;
}

void printArray(const int grades[][EXAMS], int pupils, int tests)
{
    printf(u8"學生索引");
    for (int j = 0; j < tests; ++j) {
        printf("   [%d]", j);
    }
    putchar('\n');
    for (int i = 0; i < pupils; ++i) {
        printf("    [%d]", i);
        for (int j = 0; j < tests; ++j) {
            printf("%6d", grades[i][j]);
        }
        putchar('\n');
    }
}

int main(void)
{
    use_utf8_console();
    const int studentGrades[STUDENTS][EXAMS] = {
        {77, 68, 86, 73},
        {96, 87, 89, 78},
        {70, 90, 86, 81}
    };
    printArray(studentGrades, STUDENTS, EXAMS);
    printf(u8"最低成績：%d\n", minimum(studentGrades, STUDENTS, EXAMS));
    printf(u8"最高成績：%d\n", maximum(studentGrades, STUDENTS, EXAMS));
    for (int student = 0; student < STUDENTS; ++student) {
        printf(u8"學生 %d 的平均成績：%.2f\n",
               student, average(studentGrades[student], EXAMS));
    }
    return 0;
}
