#include <stdio.h>
#include "../console.h"
#define SIZE 10

int main(void)
{
    use_utf8_console();
    int s[SIZE];
    for (int j = 0; j < SIZE; ++j) {
        s[j] = 2 + 2 * j;
    }
    puts(u8"索引    數值");
    for (int j = 0; j < SIZE; ++j) {
        printf("%4d %7d\n", j, s[j]);
    }
    return 0;
}
