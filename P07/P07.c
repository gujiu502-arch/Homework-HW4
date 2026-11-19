#include <stdio.h>
#include "../console.h"
#define SIZE 12

int main(void)
{
    use_utf8_console();
    int a[SIZE] = {1, 3, 5, 4, 7, 2, 99, 16, 45, 67, 89, 45};
    int total = 0;
    for (int i = 0; i < SIZE; ++i) {
        total += a[i];
    }
    printf(u8"陣列元素總和為 %d\n", total);
    return 0;
}
