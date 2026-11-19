#include <stdio.h>
#include "../console.h"

int main(void)
{
    use_utf8_console();
    int n[10];
    for (int i = 0; i < 10; ++i) {
        n[i] = 0;
    }
    puts(u8"索引    數值");
    for (int i = 0; i < 10; ++i) {
        printf("%4d %7d\n", i, n[i]);
    }
    return 0;
}
