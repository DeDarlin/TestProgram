#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#undef byte
#include <string>
#include <fstream>
#include "TestProgram.h"
#include "Menu.h"
#include "md5.h"
#include "User.h"
#include "Admin.h"
#include "functions.h"

using namespace std;

bool TestProgram::InSystem(string login)
{
	ifstream in("Guests.txt");
	bool flag = false;
	if (in.is_open())
	{
		string temp;
		size_t c = CountLines("Guests.txt");
		for (size_t i = 0; i < c; i++)
		{
			in >> temp;
			if (temp == login)
			{
				flag = true; break;
			}
		}
	}
	in.close();
	return flag;
}

string TestProgram::RemoveSpaces(const string& s)
{
	string out;
	out.reserve(s.size());
	for (char c : s) {
		if (c != ' ') out.push_back(c);
	}
	return out;
}

void TestProgram::SingIn()
{
	system("cls");
	string login, password;
	gotoxy(x, y);
	cout << "Введіть ПІБ: "; getline(cin, login);
	login = RemoveSpaces(login);
	gotoxy(x, y + 1);
	cout << "Введіть пароль: "; getline(cin, password);

	ifstream in("Users.txt");
	if (!in.is_open())
	{
		system("cls");
		gotoxy(x, y);
		cout << "Файл не знайдено" << endl;
		Sleep(1000);
		return;
	}

	string temp_login, temp_password;
	bool flag = false;
	size_t s = static_cast<size_t>(-1);
	size_t i = 0;

	while (in >> temp_login >> temp_password)
	{
		if (temp_login == login && temp_password == md5(password))
		{
			flag = true;
			s = i;
			break;
		}
		++i;
	}
	in.close();

	if (!flag)
	{
		system("cls");
		gotoxy(x, y);
		cout << "Введені не вірні дані" << endl;
		Sleep(1000);
		return;
	}

	if (s == 0)
	{
		Admin admin(login, password);
		admin.menu();
	}
	User user(login, password);
	user.menu();
}

void TestProgram::SingUp()
{
	system("cls");

	struct Abonent
	{
		string login, password, home_address, mobile_number;
	};

	Abonent current;
	gotoxy(x, y);
	cout << "Введіть ПІБ: "; getline(cin, current.login);
	current.login = RemoveSpaces(current.login);

	if (InSystem(current.login) == true)
	{
		system("cls");
		gotoxy(x, y);
		cout << "Аккаунт з таким ПІБ вже створений" << endl;
		Sleep(1000);
		return;
	}

	gotoxy(x, y + 1);
	cout << "Введіть пароль: "; getline(cin, current.password);
	gotoxy(x, y + 2);
	cout << "Введіть домашню адресу: "; getline(cin, current.home_address);
	gotoxy(x, y + 3);
	cout << "Введіть мобільний телефон: "; getline(cin, current.mobile_number);

	ofstream out("Users.txt", ios::app);
	out << current.login << " " << md5(current.password) << " " << current.home_address << " " << current.mobile_number << endl;
	out.close();

	system("cls");
	gotoxy(x, y);
	cout << "Реєстрація успішна" << endl;
	Sleep(1000);
}

void TestProgram::start()
{
	while (true)
	{
		system("cls");
		int c = Menu::select_vertical({ "Вхід", "Реєстрація", "Вихід" }, HorizontalAlignment::Center, 12);
		switch (c)
		{
		case 0:
			SingIn();
			break;
		case 1:
			SingUp();
			break;
		case 2:
			exit(0);
		}
	}
}