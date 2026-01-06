#pragma once
#include <string>

enum class Role
{
	Admin,
	User
};

class TestProgram
{
public:

	bool UserExists(const std::string& login);

	Role DetectRole(const std::string& login);

	void SignIn();

	void SignUp();

	void Run();
};