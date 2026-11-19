#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../console.h"
#define SIZE 100

int linearSearch(const int array[], int key, int size)
{
    for (int i = 0; i < size; ++i) {
        if (array[i] == key) {
            return i;
        }
    }
    return -1;
}

int main(void)
{
    use_utf8_console();
    int a[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        a[i] = 2 * i;
    }
    char line[80], *end;
    fputs(u8"請輸入搜尋用的整數（陣列為 0、2、4 到 198，例如 36）：", stderr);
    fflush(stderr);
    if (!fgets(line, sizeof line, stdin) || !strchr(line, '\n')) {
        fputs(u8"輸入錯誤。請輸入一個整數並按 Enter。\n", stderr);
        return 1;
    }
    errno = 0;
    long value = strtol(line, &end, 10);
    if (end == line || errno == ERANGE || value < INT_MIN || value > INT_MAX ||
        end[strspn(end, " \t\r\n")] != '\0') {
        fputs(u8"輸入錯誤。請輸入一個 int 範圍內的整數。\n", stderr);
        return 1;
    }
    int element = linearSearch(a, (int)value, SIZE);
    if (element == -1) {
        puts(u8"找不到指定數值。");
    } else {
        printf(u8"找到數值 %ld，陣列索引為 %d。\n", value, element);
    }
    return 0;
}
