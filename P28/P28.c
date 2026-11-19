#include <stdio.h>
#include "../console.h"
#define SIZE 5

void modifyArray(int b[], int size)
{
    for (int i = 0; i < size; ++i) {
        b[i] *= 2;
    }
}

void modifyElement(int e)
{
    e *= 2;
    printf(u8"函式內的副本為 %d\n", e);
}

int main(void)
{
    use_utf8_console();
    int a[SIZE] = {0, 1, 2, 3, 4};
    puts(u8"傳遞陣列前");
    for (int i = 0; i < SIZE; ++i) {
        printf("%d%c", a[i], i == SIZE - 1 ? '\n' : ' ');
    }
    modifyArray(a, SIZE);
    puts(u8"傳遞陣列後");
    for (int i = 0; i < SIZE; ++i) {
        printf("%d%c", a[i], i == SIZE - 1 ? '\n' : ' ');
    }
    printf(u8"傳遞單一元素前 a[3] = %d\n", a[3]);
    modifyElement(a[3]);
    printf(u8"傳遞單一元素後 a[3] = %d\n", a[3]);
    return 0;
}
