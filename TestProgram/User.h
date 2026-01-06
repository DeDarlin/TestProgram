#pragma once

class User
{
	std::string login, password;

public:

	User(const std::string& login, const std::string& password)
		: login(login), password(password) {}

	void Categories(bool inAdmin = false);

	void Results() const;

	void menu();

    const string& getLogin() const { return login; }
};

