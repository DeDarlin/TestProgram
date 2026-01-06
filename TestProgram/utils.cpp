#include "utils.h"

#include <fstream>
#include <string>
#include <vector>

size_t utils::CountLines(const std::string& filename)
{
    std::ifstream ifs(filename);
    if (!ifs)
    {
        throw std::runtime_error("Failed open file ");
    }

    std::string line;
    size_t counter = 0;
    while (std::getline(ifs, line)) counter++;
    return counter;
}

void utils::RemoveLine(const std::string& filename, std::string line)
{
    std::ifstream in(filename);
    std::vector<std::string> file;
    std::string temp;

    if (!in.is_open()) return;

    while (std::getline(in, temp))
        if (temp != line)
            file.push_back(temp);

    in.close();

    std::ofstream out(filename);
    for (const auto& s : file)
        out << s << std::endl;

    out.close();
}

std::string utils::RemoveSpaces(const std::string s) {
	std::string out;
	out.reserve(s.size());
	for (char c : s) {
		if (c != ' ') out.push_back(c);
	}
	return out;
}
