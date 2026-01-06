#pragma once
#include <string>
#include "User.h"

class Admin : public User
{

public:
	Admin(const std::string login, const std::string password)
		: User(login, password) {}

	void AddCategory();

	void DeleteCategory();

	void WorkWithTests();

	void UsersResults();

	void menu();
};

