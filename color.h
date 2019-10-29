#pragma once

#include "windows.h"
#include <vector>

typedef struct color { int r; int g; int b; };

color const RED = { 255, 0, 0 };
color const REDORANGE = { 255, 83, 0 };
color const ORANGE = { 255, 165, 0 };
color const ORANGEYELLOW = { 255, 210, 0 };
color const YELLOW = { 255, 255, 0 };
color const YELLOWGREEN = { 127, 255, 0 };
color const GREEN = { 0, 255, 0 };
color const GREENBLUE = { 0, 127, 127 };
color const BLUE = { 0, 0, 255 };
color const BLUEINDIGO = { 37, 0, 192 };
color const INDIGO = { 75, 0, 130 };

color const NOTETOCOLOR[] = {RED,REDORANGE,ORANGE,ORANGEYELLOW,YELLOW,YELLOWGREEN,GREEN,GREENBLUE,BLUE,BLUEINDIGO,INDIGO};

color getColor(int note);
color mixColor(vector<int>& note);
void convertColor(color cl, COLORREF& cref);