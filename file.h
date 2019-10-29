#pragma once

#include <fstream>
#include <string>

using namespace std;

bool loadFile(CString filePath, std::ifstream& fs);
int rowsFile(std::ifstream& fs);
void startFile(std::ifstream& fs);
