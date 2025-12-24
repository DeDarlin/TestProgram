#pragma once
#include <fstream>
#include <string>

using namespace std;

const int x = 45, y = 12;

size_t CountLines(const string& filename);

void RemoveLine(const string& filename, string line);