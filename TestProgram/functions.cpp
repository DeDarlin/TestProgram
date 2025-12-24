#include"functions.h"

#include <fstream>
#include <string>
#include <vector>

using namespace std;

size_t CountLines(const string& filename)
{
    ifstream ifs(filename);
    if (!ifs)
    {
        throw runtime_error("Failed open file ");
    }

    string line;
    size_t counter = 0;
    while (getline(ifs, line)) counter++;
    return counter;
}

void RemoveLine(const string& filename, string line)
{
    ifstream in(filename);
    vector<string> file;
    string temp;

    if (!in.is_open()) return;

    while (getline(in, temp))
        if (temp != line)
            file.push_back(temp);

    in.close();

    ofstream out(filename);
    for (const auto& s : file)
        out << s << endl;

    out.close();
}