#pragma once
#include <string>
#include <vector>

class Category
{
    std::string user;
    std::string categoryName;
    std::vector<std::string> tests;

public:

    Category(const std::string& user, const std::string& categoryName)
        : user(user), categoryName(categoryName) {
        LoadTests();
    }

    bool LoadTests();

    void Delete();

    void DeleteTest();

    void Tests();

    void NewTest();

    void adminMenu();

    void menu();
};