#include "Console.h"
#include "TestProgram.h"

int main()
{
	Console::InitUtf8();

    TestProgram app;
    app.Run();

    return 0;
}