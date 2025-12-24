#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "functions.h"

using namespace std;

class Category
{
	string user;
	string current;
	vector<string> tests;

public:

	Category(const string& user, const string& current) : user(user), current(current)
	{ 
		ifstream in(current + ".txt");
		if (in.is_open())
		{
			int size = CountLines(current + ".txt");
			for (size_t i = 0; i < size; i++)
			{
				string temp;
				in >> temp;
				tests.push_back(temp);
			}
		}
		else
			tests.push_back("N");
		in.close();
	}

	void Delete();

	void DeleteTest();

	void Tests();

	void NewTest();

	void adminMenu();
	
	void menu();
};

