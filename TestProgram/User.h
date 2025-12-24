#pragma once

using namespace std;

class User
{
	string login, password;

public:

	User(string login, string password) : login(login), password(password) {}

	void Categories(int inAdmin = 0);

	void Results();

	void menu();

    string getLogin() const { return login; }
};

