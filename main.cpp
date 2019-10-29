#include "file.h"
#include "color.h"
#include "sheet.h"
#include <iostream>
#include <vector> 
#include <windows.h>
#include <math.h>

using namespace std;

static HWND sHwnd;

void SetWindowHandle(HWND hwnd) {

	sHwnd = hwnd;

}

void setPixel(int x, int y, COLORREF& color) {

	if (sHwnd == NULL) {

		MessageBox(NULL, "sHwnd was not initialized !", "Error", MB_OK | MB_ICONERROR);

		exit(0);

	}

	HDC hdc = GetDC(sHwnd);

	SetPixel(hdc, x, y, color);

	ReleaseDC(sHwnd, hdc);

	return;

	// NEVERREACH //

}

float const A49 = 440;
float const TIMEBASE = 32;

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		cout << "Invalid command: Missing file path";
		return 0;
	}

	std::ifstream fs;
	string note32;
	int fileSize;

	if (loadFile(argv[1], fs))
	{
		sheet musicSheet(rowsFile(fs),256);
		
		string str;
		int row = 0, col;
		
		startFile(fs);
		
		while (getline(fs, str))
		{
			col = 0;
			int f = str.find(' ');
			while (f >= 0)
			{
				musicSheet[row][col] = stoi(str.substr(0,f));
				str = str.substr(f + 1);
				f = str.find(' ');
				col++;
			}
			musicSheet[row][col] = stoi(str);
			/*int sound = 0;
			for (int cnt = 1; cnt <= col; cnt++)
			{
				sound += musicSheet[row][cnt];
			}
			Beep(A49 * pow(2, (sound - col * 49.0000)) / 12.000, 1000.0000 * musicSheet[row][0] / TIMEBASE);*/
			row++;
		}
		fileSize = musicSheet.size();
		/*for (int cnt = 1; cnt < 89; cnt++)
		{
			color cl = getColor(cnt);
			if ((cl.r < 0) || (cl.g < 0) || (cl.b < 0) || (cl.r > 255) || (cl.g > 255) || (cl.b > 255))
			{
				cout << "Not working for " << cnt << endl;
			}
		}*/
		int pictureS = pictureSize(musicSheet.time_size());
		color cl = { 124, 124, 124 };
		COLORREF cref;

		LPCSTR wclass = "MusicToColor";
		LPCSTR wtitle = "MusicToColor";

		HWND hwnd = CreateWindowEx(NULL,
			wclass,    // name of the window class
			wtitle,   // title of the window
			WS_OVERLAPPEDWINDOW,    // window style
			300,    // x-position of the window
			300,    // y-position of the window
			500,    // width of the window
			400,    // height of the window
			NULL,    // we have no parent window, NULL
			NULL,    // we aren't using menus, NULL
			NULL,    // application handle
			NULL);
		SetWindowHandle(hwnd);
		for (int cnt = 0; cnt < 1000; cnt++)
		{
			convertColor(cl, cref);
			setPixel(cnt, cnt, cref);
		}
	}
}