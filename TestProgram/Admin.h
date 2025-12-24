#pragma once
#include "User.h"

using namespace std;

class Admin : public User
{
public:
	Admin(string login, string password) : User(login, password) {}

	void AddCategory();

	void DeleteCategory();

	void WorkWithTests();

	void WorkWithUsers();

	void menu();
};

