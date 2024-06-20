
#include <windows.h>
#include <string>



void PrintMsg(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

int main()
{
    int count = 0;
    do
    {
        PrintMsg("%d Hello World\n", count);
        Sleep(2000);
        count++;

    } while (true);


    return 0;
}
