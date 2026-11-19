#include <stdio.h>
#include "../console.h"
#define SIZE 10

int main(void)
{
    use_utf8_console();
    int n[SIZE] = {19, 3, 15, 7, 11, 9, 13, 5, 17, 1};
    puts(u8"索引    數值    星號圖");
    for (int i = 0; i < SIZE; ++i) {
        printf("%4d %7d    ", i, n[i]);
        for (int j = 0; j < n[i]; ++j) {
            putchar('*');
        }
        putchar('\n');
    }
    return 0;
}
