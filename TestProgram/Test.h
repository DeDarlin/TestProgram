#pragma once

using namespace std;

class Test
{
	string current;

public:
	Test(string current) : current(current) {}

	void Delete();

	string start();
};