#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#undef byte
#include <string>
#include <iostream>
#include <fstream>
#include "TestProgram.h"
#include "Menu.h"
#include "md5.h"
#include "User.h"
#include "Admin.h"
#include "utils.h"
#include "Console.h"

bool TestProgram::UserExists(const std::string& login)
{
	std::ifstream in("Users.txt");
	if (!in) return false;

	std::string fileLogin;
	while (in >> fileLogin)
	{
		if (fileLogin == login)
			return true;

		std::string skip;
		std::getline(in, skip);
	}
	return false;
}

Role TestProgram::DetectRole(const std::string& login)
{
	ifstream in("Users.txt");
	if (!in.is_open())
	{
		std::string tlogin;
		in >> tlogin;
		if (tlogin == login)
		return Role::Admin;
	}
	in.close();

	return Role::User;
}

void TestProgram::SignIn()
{
	Console::Clear();
	std::string login, password;
	gotoxy(x, y);
	std::cout << "Введіть ПІБ: "; std::getline(cin, login);
	login = utils::RemoveSpaces(login);
	gotoxy(x, y + 1);
	std::cout << "Введіть пароль: "; std::getline(cin, password);

	ifstream in("Users.txt");
	if (!in.is_open())
	{
		Console::Clear();
		gotoxy(x, y);
		cout << "Файл не знайдено" << endl;
		Console::SleepMs(1000);
		return;
	}

	std::string tlogin;
	std::string tpass;
	std::string rest;
	bool flag = false;
	size_t i = 0;

	while (in >> tlogin >> tpass)
	{
		if (tlogin == login && tpass == md5(password))
		{
			flag = true;
			break;
		}
		std::getline(in, rest);
	}
	in.close();

	if (!flag)
	{
		Console::Clear();
		gotoxy(x, y);
		std::cout << "Введені не вірні дані" << endl;
		Console::SleepMs(1000);
		return;
	}

	Role role = DetectRole(login);

	if (role == Role::Admin)
	{
		Admin admin(login, password);
		admin.menu();
	}
	else
	{
		User user(login, password);
		user.menu();
	}
}

void TestProgram::SignUp()
{
	Console::Clear();

	struct Abonent
	{
		std::string login;
		std::string password;
		std::string home_address;
		std::string mobile_number;
	};

	Abonent current;
	gotoxy(x, y);
	std::cout << "Введіть ПІБ: "; std::getline(cin, current.login);
	current.login = utils::RemoveSpaces(current.login);

	if (UserExists(current.login) == true)
	{
		Console::Clear();
		gotoxy(x, y);
		std::cout << "Аккаунт з таким ПІБ вже створений" << endl;
		Console::SleepMs(1000);
		return;
	}

	gotoxy(x, y + 1);
	std::cout << "Введіть пароль: "; std::getline(cin, current.password);
	gotoxy(x, y + 2);
	std::cout << "Введіть домашню адресу: "; std::getline(cin, current.home_address);
	gotoxy(x, y + 3);
	std::cout << "Введіть мобільний телефон: "; std::getline(cin, current.mobile_number);

	ofstream out("Users.txt", ios::app);
	out << current.login << " " << md5(current.password) << " " << current.home_address << " " << current.mobile_number << endl;
	out.close();

	Console::Clear();
	gotoxy(x, y);
	std::cout << "Реєстрація успішна" << endl;
	Console::SleepMs(1000);
}

void TestProgram::Run()
{
	while (true)
	{
		Console::Clear();
		int c = Menu::select_vertical({ "Вхід", "Реєстрація", "Вихід" }, HorizontalAlignment::Center, 12);
		switch (c)
		{
		case 0:
			SignIn();
			break;
		case 1:
			SignUp();
			break;
		case 2:
			exit(0);
		}
	}
}