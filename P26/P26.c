#include <stdio.h>
#include "../console.h"

int main(void)
{
    use_utf8_console();
    char array[5];
    printf("array     = %p\n", (void *)array);
    printf("&array[0] = %p\n", (void *)&array[0]);
    printf("&array    = %p\n", (void *)&array);
    puts(u8"三個位址值相同，指標型別與位移單位仍有差異。");
    return 0;
}
