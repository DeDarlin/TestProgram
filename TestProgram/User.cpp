#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "User.h"
#include "Menu.h"
#include "utils.h"
#include "Category.h"
#include "Console.h"

void User::Categories(bool isAdmin)
{
	Console::Clear();
	std::vector<std::string> Categories;
	std::ifstream in("Categories.txt");

	if (!in.is_open())
	{
		gotoxy(x, y);
		cout << "Пока категорій немає";
		Console::SleepMs(1000);
		return;
	}

	
	std::string temp;
	while (std::getline(in, temp))
	{
		if (!temp.empty())
			Categories.push_back(temp);
	}
	in.close();
	Categories.push_back("Вихід");

	int c = Menu::select_vertical({ Categories }, HorizontalAlignment::Center, 12);

	if (c == Categories.size() - 1) return;

	Category category(getLogin(), Categories[c]);
	isAdmin ? category.adminMenu() : category.menu();
}

void User::Results() const
{ 
	Console::Clear();
	std::ifstream in(login + "_statistic.txt");
	if (in.is_open())
	{
		std::string temp1, temp2;
		int size = utils::CountLines(login + "_statistic.txt");
		for (size_t i = 0; i < size; i++)
		{
			gotoxy(x, y + i);
			in >> temp1 >> temp2;
			std::cout << temp1 << " " << temp2 << endl;
		}
	}
	else
	{
		gotoxy(x, y);
		std::cout << "Поки немає результатів";
	}
	Console::SleepMs(1000);
}

void User::menu()
{
	while (true)
	{
		Console::Clear();
		int c = Menu::select_vertical({ "Категорії", "Результати", "Вихід" }, HorizontalAlignment::Center, 12);
		switch (c)
		{
		case 0:
			Categories();
			break;
		case 1:
			Results();
			break;
		case 2:
			return;
		}
	}
}