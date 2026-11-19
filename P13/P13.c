#include <stdio.h>
#include "../console.h"

void printArray(const int a[][3])
{
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%d%c", a[i][j], j == 2 ? '\n' : ' ');
        }
    }
}

int main(void)
{
    use_utf8_console();
    const int array1[2][3] = {{1, 2, 3}, {4, 5, 6}};
    const int array2[2][3] = {{1, 2, 3}, {4, 5}};
    const int array3[2][3] = {{1, 2}, {4}};
    puts(u8"陣列 1 的各列");
    printArray(array1);
    puts(u8"陣列 2 的各列");
    printArray(array2);
    puts(u8"陣列 3 的各列");
    printArray(array3);
    return 0;
}
