#include <fstream>
#include "Test.h"
#include "Menu.h"
#include "utils.h"
#include "Console.h"

void Test::Delete()
{
	std::string temp = current + ".txt";
	remove(temp.c_str());
}

std::string Test::start()
{
	Console::Clear();
	int ques = utils::CountLines(current + ".txt");
	int stat = 0;
	std::ifstream in(current + ".txt");
	for (size_t i = 0; i < ques; i++)
	{
		gotoxy(x + 10, y - 4);
		std::cout << current;
		gotoxy(x + 10, y - 3);
		std::cout << i << " / " << ques;

		std::string temp;
		in >> temp;
		gotoxy(x + 10, y - 1);
		std::cout << temp;
		int answ, correct;
		in >> answ;
		std::vector<std::string> answr;
		for (size_t i = 0; i < answ; i++)
		{
			in >> temp;
			answr.push_back(temp);
		}
		in >> correct;
		int c = Menu::select_vertical({ answr }, HorizontalAlignment::Center, 12);
		if (c + 1 == correct)
		{
			stat++;
		}
	}
	Console::Clear();
	gotoxy(x + 5, y - 1);
	std::cout << current;
	gotoxy(x + 5, y);
	std::cout << ques << "/" << stat;
	Console::SleepMs(1000);
	in.close();
	std::string temp = to_string(ques) + "/" + to_string(stat);
	return temp;
}