#include <cstdio>
#include "../console.h"

int addbyone(int &xref)
{
    ++xref;
    std::printf("xref = %d\n", xref);
    return xref;
}

int main()
{
    use_utf8_console();
    int x = 100;
    std::printf(u8"呼叫前 x = %d\n", x);
    int y = addbyone(x);
    std::printf(u8"呼叫後 x = %d\n回傳值 y = %d\n", x, y);
    return 0;
}
