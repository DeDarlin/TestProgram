#include <fstream>
#include "Category.h"
#include "Menu.h"
#include "functions.h"
#include "Test.h"

void Category::Delete()
{
	cout << tests[0];
	if (tests[0] != "N")
	{
		int size = CountLines(current + ".txt");
		for (size_t i = 0; i < size; i++)
		{
			Test test(tests[i]);
			test.Delete();
		}
		string temp = current + ".txt";
		remove(temp.c_str());
	}

	RemoveLine("Categories.txt", current);
}

void Category::DeleteTest()
{
	int size = tests.size();
	vector<string> temp = tests;
	temp.push_back("Вихід");

	int c = Menu::select_vertical({ temp }, HorizontalAlignment::Center, 12);

	if (c == temp.size() - 1) return;

	Test test(tests[c]);
	test.Delete();
}

void Category::Tests()
{
	vector<string> Tests;
	ifstream in(current + ".txt");

	if (!in.is_open())
	{
		gotoxy(x, y);
		cout << "Пока тестів немає";
		Sleep(1000);
		return;
	}

	int size = CountLines(current + ".txt");
	for (size_t i = 0; i < size; i++)
	{
		string temp;
		in >> temp;
		Tests.push_back(temp);
	}
	in.close();
	Tests.push_back("Вихід");

	int c = Menu::select_vertical({ Tests }, HorizontalAlignment::Center, 12);

	if (c == Tests.size() - 1) return;

	Test test(Tests[c]);
	string result = test.start();
	ofstream out(user + "_statistic.txt", ios::app);
	out << Tests[c] << " " << result << endl;
}

void Category::NewTest()
{
	system("cls");
	gotoxy(x, y);

	string name, question, answer;
	cout << "Введіть назву тесту: "; 
	getline(cin, name);

	ofstream out(name + ".txt");
	int count = 1;
	int cor;

	while (true)
	{
		system("cls");
		gotoxy(x, y);

		//int countAnsw = 0;
		cout << "Введіть питання №" << count << ": ";
		getline(cin, question);

		out << question << " ";

		int countAnsw = 0;

		gotoxy(x, y + 1);
		cout << "Введіть кількість відповідей: ";
		while (!(cin >> countAnsw) || countAnsw <= 1)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Кількість має бути > 1. Спробуйте ще раз: ";
		}
		cin.ignore();

		out << countAnsw << " ";

		for (size_t i = 0; i < countAnsw; i++)
		{
			gotoxy(x, y + i + 2);
			cout << "Введіть відповідь №" << i + 1 << ": ";
			getline(cin, answer);
			out << answer << " ";
		}

		gotoxy(x, y + countAnsw + 2);
		while (true)
		{
			cout << "Номер правильної відповіді (1-" << countAnsw << "): ";
			if (cin >> cor && cor >= 1 && cor <= countAnsw)
				break;

			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Невірний номер. Спробуйте ще раз." << endl;
		}
		cin.ignore();

		out << cor << endl;

		system("cls");
		gotoxy(x, y);
		cout << "Питання створене";
		Sleep(1000);

		system("cls");
		gotoxy(x, y - 1);
		cout << "Створити ще одне питання?";

		int c = Menu::select_vertical({ "Так", "Ні" }, HorizontalAlignment::Center, 12);
		if (c == 1)
			break;

		count++;
	}
	out.close();

	out.open(current + ".txt", ios::app);
	out << name << endl;
	out.close();
}

void Category::adminMenu()
{
	while (true)
	{
		system("cls");
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
		system("cls");
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