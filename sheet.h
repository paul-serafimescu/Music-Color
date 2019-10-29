#pragma once
#include <vector>

using namespace std;

class sheet
{
public:
	sheet()
	{
		tab_.resize(0);
	}
	sheet(int rows, int cols)
	{
		tab_.resize(rows);
		for (auto& row : tab_)
		{
			row.resize(cols);
		}
	}

	vector<int>& operator[](int row) { return tab_[row]; }

	int size()
	{
		return tab_.size();
	}

	int time_size()
	{
		int totalTime = 0;
		for (int cnt = 0; cnt < tab_.size(); cnt++)
		{
			totalTime += tab_[cnt][0];
		}
		return totalTime;
	}
private:
	vector<vector<int> > tab_;
};