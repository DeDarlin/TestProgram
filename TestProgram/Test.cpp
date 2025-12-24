#include <fstream>
#include "Test.h"
#include "Menu.h"
#include "functions.h"

void Test::Delete()
{
	string temp = current + ".txt";
	remove(temp.c_str());
}

string Test::start()
{
	system("cls");
	int ques = CountLines(current + ".txt");
	int stat = 0;
	ifstream in(current + ".txt");
	for (size_t i = 0; i < ques; i++)
	{
		gotoxy(x + 10, y - 4);
		cout << current;
		gotoxy(x + 10, y - 3);
		cout << i << " / " << ques;

		string temp;
		in >> temp;
		gotoxy(x + 10, y - 1);
		cout << temp;
		int answ, correct;
		in >> answ;
		vector<string> answr;
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
	system("cls");
	gotoxy(x + 5, y - 1);
	cout << current;
	gotoxy(x + 5, y);
	cout << ques << "/" << stat;
	Sleep(1000);
	in.close();
	string temp = to_string(ques) + "/" + to_string(stat);
	return temp;
}