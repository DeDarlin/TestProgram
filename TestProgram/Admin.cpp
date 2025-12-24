#include <fstream>
#include "Admin.h"
#include "Menu.h"
#include "functions.h"
#include "Category.h"

void Admin::AddCategory()
{
	system("cls");
	gotoxy(x, y);
	string NewCategory;
	cout << "Введіть назву нової категорії:"; getline(cin, NewCategory);
	ofstream out("Categories.txt", ios::app);
	out << NewCategory << endl;
	gotoxy(x, y + 1);
	cout << "Категорія успішно додана";
}

void Admin::DeleteCategory()
{
	system("cls");
	gotoxy(x, y - 1);
	cout << "Виберіть категорію для видалення: ";

	vector<string> Categories;
	ifstream in("Categories.txt");
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

	if (c == Categories.size() - 1) exit(0);

	in.close();
	Category category(getLogin(), Categories[c]);
	category.Delete();
}

void Admin::WorkWithTests()
{
	while (true)
	{
		system("cls");
		int c = Menu::select_vertical({ "Категорії", "Створити категорію", "Видалити категорію", "Вихід" }, HorizontalAlignment::Center, 12);
		switch (c)
		{
		case 0:
			User::Categories(1);
			break;
		case 1:
			AddCategory();
			break;
		case 2:
			DeleteCategory();
			break;
		case 3:
			return;
		}
	}
}

void Admin::WorkWithUsers()
{
	system("cls");
	gotoxy(x, y);
	ifstream in("Users.txt");
	if (in.is_open())
	{
		string temp, a, b, c;
		int size = CountLines("Users.txt");
		for (size_t i = 0; i < size; i++)
		{
			in >> temp >> a >> b >> c;
			gotoxy(x - 10, y + i);
			cout << temp;
			Results();
		}
		Sleep(2000);
	}
	else
		cout << "Поки немає користувачів";
	Sleep(2000);
}

void Admin::menu()
{
	while (true)
	{
		system("cls");
		int c = Menu::select_vertical({ "Управління тестами", "Управління користувачами", "Вихід" }, HorizontalAlignment::Center, 12);
		switch (c)
		{
		case 0:
			WorkWithTests();
			break;
		case 1:
			WorkWithUsers();
			break;
		case 2:
			return;
		}
	}
}