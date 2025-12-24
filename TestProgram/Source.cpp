#include <iostream>
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#undef byte
#include "TestProgram.h"

using namespace std;

void main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	//string current = "User";
	//cout << current + ".txt";
	TestProgram test;
	test.start();
}