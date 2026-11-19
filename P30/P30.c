#include <stdio.h>
#include "../console.h"

void inverse(int *b)
{
    int tmp[3];
    for (int i = 0; i < 3; ++i) {
        tmp[2 - i] = b[i];
    }
    for (int i = 0; i < 3; ++i) {
        b[i] = tmp[i];
    }
}

int main(void)
{
    use_utf8_console();
    int a[3] = {3, 5, 7};
    printf(u8"反轉前：%d %d %d\n", a[0], a[1], a[2]);
    inverse(a);
    printf(u8"反轉後：%d %d %d\n", a[0], a[1], a[2]);
    return 0;
}
