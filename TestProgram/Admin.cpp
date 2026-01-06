#include <fstream>
#include "Admin.h"
#include "Menu.h"
#include "utils.h"
#include "Category.h"
#include "Console.h"

void Admin::AddCategory()
{
	Console::Clear();
	gotoxy(x, y);
	std::string NewCategory;
	std::cout << "Введіть назву нової категорії:"; std::getline(cin, NewCategory);
	std::ofstream out("Categories.txt", ios::app);
	out << NewCategory << endl;
	gotoxy(x, y + 1);
	std::cout << "Категорія успішно додана";
}

void Admin::DeleteCategory()
{
	Console::Clear();
	gotoxy(x, y - 1);
	cout << "Виберіть категорію для видалення: ";

	std::vector<std::string> Categories;
	std::ifstream in("Categories.txt");
	int size = utils::CountLines("Categories.txt");
	for (size_t i = 0; i < size; i++)
	{
		std::string temp;
		std::getline(in, temp);
		Categories.push_back(temp);
	}
	in.close();
	Categories.push_back("Вихід");

	int c = Menu::select_vertical({ Categories }, HorizontalAlignment::Center, 12);

	if (c == Categories.size() - 1) return;

	Category category(getLogin(), Categories[c]);
	category.Delete();
}

void Admin::WorkWithTests()
{
	while (true)
	{
		Console::Clear();
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

void Admin::UsersResults()
{
	Console::Clear();
	gotoxy(x, y);
	std::ifstream in("Users.txt");
	if (in.is_open())
	{
		std::string temp, a, b, c;
		int size = utils::CountLines("Users.txt");
		for (size_t i = 0; i < size; i++)
		{
			in >> temp >> a >> b >> c;
			gotoxy(x - 10, y + i);
			std::cout << temp;
			Results();
		}
		Console::SleepMs(2000);
	}
	else
		std::cout << "Поки немає користувачів";
	Console::SleepMs(2000);
}

void Admin::menu()
{
	while (true)
	{
		Console::Clear();
		int c = Menu::select_vertical({ "Управління тестами", "Управління користувачами", "Вихід" }, HorizontalAlignment::Center, 12);
		switch (c)
		{
		case 0:
			WorkWithTests();
			break;
		case 1:
			UsersResults();
			break;
		case 2:
			return;
		}
	}
}