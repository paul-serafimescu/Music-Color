#include "pch.h"

bool loadFile(CString filePath, std::ifstream& fs)
{
	fs.open(filePath, ifstream::in);
	return !fs.fail();
}

int rowsFile(std::ifstream& fs)
{
	int rows = 0;
	string str;
	while (getline(fs, str))
	{
		rows++;
	}
	return rows;
}

void startFile(std::ifstream& fs)
{
	fs.clear();
	fs.seekg(0, ios::beg);
}