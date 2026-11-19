#include <stdio.h>
#include "../console.h"

void staticArrayInit(void)
{
    static int array1[3];
    puts(u8"進入靜態陣列函式");
    for (int i = 0; i < 3; ++i) {
        printf("array1[%d] = %d%c", i, array1[i], i == 2 ? '\n' : ' ');
    }
    puts(u8"離開靜態陣列函式");
    for (int i = 0; i < 3; ++i) {
        array1[i] += 5;
        printf("array1[%d] = %d%c", i, array1[i], i == 2 ? '\n' : ' ');
    }
}

void automaticArrayInit(void)
{
    int array2[3] = {1, 2, 3};
    puts(u8"進入自動陣列函式");
    for (int i = 0; i < 3; ++i) {
        printf("array2[%d] = %d%c", i, array2[i], i == 2 ? '\n' : ' ');
    }
    puts(u8"離開自動陣列函式");
    for (int i = 0; i < 3; ++i) {
        array2[i] += 5;
        printf("array2[%d] = %d%c", i, array2[i], i == 2 ? '\n' : ' ');
    }
}

int main(void)
{
    use_utf8_console();
    puts(u8"第一次呼叫各函式");
    staticArrayInit();
    automaticArrayInit();
    puts(u8"\n第二次呼叫各函式");
    staticArrayInit();
    automaticArrayInit();
    return 0;
}
