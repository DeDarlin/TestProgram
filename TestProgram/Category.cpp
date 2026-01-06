#include <fstream>
#include "Category.h"
#include "Menu.h"
#include "utils.h"
#include "Test.h"
#include "Console.h"

bool Category::LoadTests()
{
	tests.clear();
	std::ifstream in(categoryName + ".txt");
	if (!in) return false;

	std::string line;
	while (std::getline(in, line))
		if (!line.empty())
			tests.push_back(line);

	return true;
}

void Category::Delete()
{
	std::cout << tests[0];
	if (tests[0] != "")
	{
		int size = utils::CountLines(categoryName + ".txt");
		for (size_t i = 0; i < size; i++)
		{
			Test test(tests[i]);
			test.Delete();
		}
		std::string temp = categoryName + ".txt";
		remove(temp.c_str());
	}

	utils::RemoveLine("Categories.txt", categoryName);
}

void Category::DeleteTest()
{
	int size = tests.size();
	std::vector < std::string > temp = tests;
	temp.push_back("Вихід");

	int c = Menu::select_vertical({ temp }, HorizontalAlignment::Center, 12);

	if (c == temp.size() - 1) return;

	Test test(tests[c]);
	test.Delete();
}

void Category::Tests()
{
	std::vector<std::string> Tests;
	std::ifstream in(categoryName + ".txt");

	if (!in.is_open())
	{
		gotoxy(x, y);
		cout << "Пока тестів немає";
		Console::SleepMs(1000);
		return;
	}

	int size = utils::CountLines(categoryName + ".txt");
	for (size_t i = 0; i < size; i++)
	{
		std::string temp;
		in >> temp;
		Tests.push_back(temp);
	}
	in.close();
	Tests.push_back("Вихід");

	int c = Menu::select_vertical({ Tests }, HorizontalAlignment::Center, 12);

	if (c == Tests.size() - 1) return;

	Test test(Tests[c]);
	std::string result = test.start();
	std::ofstream out(user + "_statistic.txt", ios::app);
	out << Tests[c] << " " << result << endl;
}

void Category::NewTest()
{
	Console::Clear();
	gotoxy(x, y);

	std::string name, question, answer;
	std::cout << "Введіть назву тесту: ";
	std::getline(cin, name);

	std::ofstream out(name + ".txt");
	int count = 1;
	int cor;

	while (true)
	{
		Console::Clear();
		gotoxy(x, y);

		std::cout << "Введіть питання №" << count << ": ";
		std::getline(cin, question);

		out << question << " ";

		int countAnsw = 0;

		gotoxy(x, y + 1);
		std::cout << "Введіть кількість відповідей: ";
		while (!(cin >> countAnsw) || countAnsw <= 1)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			std::cout << "Кількість має бути > 1. Спробуйте ще раз: ";
		}
		cin.ignore();

		out << countAnsw << " ";

		for (size_t i = 0; i < countAnsw; i++)
		{
			gotoxy(x, y + i + 2);
			std::cout << "Введіть відповідь №" << i + 1 << ": ";
			std::getline(cin, answer);
			out << answer << " ";
		}

		gotoxy(x, y + countAnsw + 2);
		while (true)
		{
			std::cout << "Номер правильної відповіді (1-" << countAnsw << "): ";
			if (cin >> cor && cor >= 1 && cor <= countAnsw)
				break;

			cin.clear();
			cin.ignore(1000, '\n');
			std::cout << "Невірний номер. Спробуйте ще раз." << endl;
		}
		cin.ignore();

		out << cor << endl;

		Console::Clear();
		gotoxy(x, y);
		cout << "Питання створене";
		Console::SleepMs(1000);

		Console::Clear();
		gotoxy(x, y - 1);
		cout << "Створити ще одне питання?";

		int c = Menu::select_vertical({ "Так", "Ні" }, HorizontalAlignment::Center, 12);
		if (c == 1)
			break;

		count++;
	}
	out.close();

	out.open(categoryName + ".txt", ios::app);
	out << name << endl;
	out.close();
}

void Category::adminMenu()
{
	while (true)
	{
		Console::Clear();
		int c = Menu::select_vertical({ "Тести", "Створити тест", "Видалити тест", "Вихід" }, HorizontalAlignment::Center, 12);
		switch (c)
		{
		case 0:
			Tests();
			break;
		case 1:
			NewTest();
			break;
		case 2:
			DeleteTest();
			break;
		case 3:
			return;
		}
	}
}

void Category::menu()
{
	while (true)
	{
		Console::Clear();
		int c = Menu::select_vertical({ "Тести", "Вихід" }, HorizontalAlignment::Center, 12);
		switch (c)
		{
		case 0:
			Tests();
			break;
		case 1:
			return;
		}
	}
}