#include <fstream>
#include "User.h"
#include "Menu.h"
#include "functions.h"
#include "Category.h"

void User::Categories(int isAdmin)
{
	system("cls");
	vector<string> Categories;
	ifstream in("Categories.txt");

	if (!in.is_open())
	{
		gotoxy(x, y);
		cout << "Пока категорій немає";
		Sleep(1000);
		return;
	}

	int size = CountLines("Categories.txt");
	for (size_t i = 0; i < size; i++)
	{
		string temp;
		in >> temp;
		Categories.push_back(temp);
	}
	in.close();
	Categories.push_back("Вихід");

	int c = Menu::select_vertical({ Categories }, HorizontalAlignment::Center, 12);

	if (c == Categories.size() - 1) return;

	if (isAdmin == 1)
	{
		Category category(getLogin(), Categories[c]);
		category.adminMenu();
	}
	else
	{
		Category category(getLogin(), Categories[c]);
		category.menu();
	}
}

void User::Results()
{ 
	system("cls");
	ifstream in(login + "_statistic.txt");
	if (in.is_open())
	{
		string temp1, temp2;
		int size = CountLines(login + "_statistic.txt");
		for (size_t i = 0; i < size; i++)
		{
			gotoxy(x, y + i);
			in >> temp1 >> temp2;
			cout << temp1 << " " << temp2 << endl;
		}
	}
	else
	{
		gotoxy(x, y);
		cout << "Поки немає результатів";
	}
	Sleep(1000);
}

void User::menu()
{
	while (true)
	{
		system("cls");
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