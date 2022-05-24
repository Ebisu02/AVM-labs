#pragma once

#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

enum COLORS { BLACK, WHITE, RED, YELLOWW, PEARPLE, BLUE, LIGHT_BLUE, GREEN };

int mt_setbgcolor(COLORS color);
int mt_setfgcolor(COLORS color);
int mt_getscreensize(int *rows, int *cols);
int mt_gotoxy(int x, int y);
int mt_clrscr();
