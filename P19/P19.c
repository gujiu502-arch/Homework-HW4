#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "../console.h"

int main(void)
{
    use_utf8_console();
    char string1[20];
    const char string2[] = "string literal";
    fputs(u8"請輸入英文單字或句子（範例 Hello there，取第一個單字）：", stderr);
    fflush(stderr);
    if (scanf("%19s", string1) != 1) {
        fputs(u8"輸入錯誤。請輸入一個單字。\n", stderr);
        return 1;
    }
    int next = getchar();
    if (next != EOF && !isspace((unsigned char)next)) {
        fputs(u8"第一個單字過長，最多可輸入 19 個字元。\n", stderr);
        return 1;
    }
    printf(u8"第一個字串：%s\n第二個字串：%s\n逐字元輸出：",
           string1, string2);
    for (size_t i = 0; i < strlen(string1); ++i) {
        printf("%c%c", string1[i], string1[i + 1] == '\0' ? '\n' : ' ');
    }
    return 0;
}
