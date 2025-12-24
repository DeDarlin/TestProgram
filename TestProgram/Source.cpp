#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#undef byte
#include "TestProgram.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    TestProgram app;
    app.start();

    return 0;
}