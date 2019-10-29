#include <math.h>
#include "pch.h"

const int BASENOTE = 49;

color getColor(int note)
{
	if (note == 0)
	{
		color cl = { 0,0,0 };
		return cl;
	}
	color startColor = NOTETOCOLOR[(note + 6) % 11];
	int shift = 12 * ((note - BASENOTE) / 12);
	if (shift < 0)
	{
		//try moving Red to Blue or Green
		if (startColor.r + shift >= 0)
		{
			startColor.r += shift;
			if (startColor.b - shift >= 0)
			{
				startColor.b -= shift;
			}
			else
			{
				startColor.g -= shift;
			}
		}
		else
		{
			//try moving Green to Blue or Red
			if (startColor.g + shift >= 0)
			{
				startColor.g += shift;
				if (startColor.b - shift >= 0)
				{
					startColor.b -= shift;
				}
				else
				{
					startColor.r -= shift;
				}
			}
			else
			{
				//try moving Blue to Green
				startColor.b += shift;
				startColor.g -= shift;
			}
		}
	}
	else
	{
		//try moving Blue to Green or Red
		if (startColor.b - shift >= 0)
		{
			startColor.b -= shift;
			if (startColor.g + shift <= 255)
			{
				startColor.g += shift;
			}
			else
			{
				startColor.r += shift;
			}
		}
		else
		{
			//try moving Green to Red or Blue
			if (startColor.g - shift >= 0)
			{
				startColor.g -= shift;
				if (startColor.r + shift <= 255)
				{
					startColor.r += shift;
				}
				else
				{
					startColor.g += shift;
				}
			}
			else
			{
				//try moving Red to Green
				startColor.r -= shift;
				startColor.g += shift;
			}
		}
	}
	return startColor;
}

color mixColor(vector<int>& note)
{
	int cnt = 0;
	color cl;
	int r = 0, g = 0, b = 0;
	//start with postition 1, 0 is length
	while (note[cnt+1] != '\0')
	{
		cl = getColor(note[cnt+1]);
		r += cl.r;
		g += cl.g;
		b += cl.b;
		cnt++;
	}
	cl.r = r / cnt;
	cl.g = g / cnt;
	cl.b = b / cnt;
	return cl;
}

void convertColor(color cl, COLORREF& cref)
{
	cref = RGB(cl.r, cl.g, cl.b);
}