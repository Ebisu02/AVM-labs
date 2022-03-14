#include "bc.h"

// `afgijklmnopqrstuvwxyz{|}~
// ◆▒°±␋┘┐┌└┼─├┤┴┬│≤≥π≠£·

int bc_printA(char * str) 
{
	cout << "\E(0" << str << "\E(B";
	return 0;
}

int bc_box(int x1, int y1, int x2, int y2) // x1 - row, y1 - column
{
	mt_gotoxy(x1, y1);
	mt_setfgcolor(GREEN);
	char* t = new char[x2 + 2];
	for (int i = 1; i < x2; ++i)
	{
		t[i] = 'p';
	}
	
	t[0] = '1';
	t[x2 + 1] = 'k';
	bc_printA(t);
	char* t1 = new char[1];
	t1[0] = 'x';
	for (int i  = x1 + 1; i < x1 + y2 + 1; ++i)
	{
		mt_gotoxy(i, y2);
		bc_printA(t1);
		mt_gotoxy(i, x1 + x2 + 1);
		bc_printA(t1);
	}
	
	mt_gotoxy(y2 + x1 + 1, y1);
	t[0] = 'n';
	t[x2 + 1] = 'j';
	bc_printA(t);
	mt_gotoxy(x1 + y2 + 2, y1 + x2 + 2);
	mt_setfgcolor(WHITE);
	return 0;
}

int bc_printbigchar(BIGCHAR chindex, int x, int y, COLORS color, COLORS color1) // x - row, y - column
{
	mt_setbgcolor(color);
	mt_setfgcolor(color1);
	char* t = new char[8];
	for (int i = 0, j = 0, ind = 0; i < 8; ++i)
	{
		if (i == 4)
		{
			ind = 1;
		}
		for (int z = 0; z < 8; ++z, ++j)
		{
			((bigchars[chindex][ind] >> j) & 0x1) == 0 ? t[j] = ' ' : t[j] = 'a'; 
		}
		mt_gotoxy(x + i, y);
		bc_printA(t);
	}
	mt_setbgcolor(BLACK);
	mt_setfgcolor(WHITE);
	mt_gotoxy(18, 0);
	return 0;	
}

int bc_setbigcharpos(int * big, int x, int y, int value) // x - row, y - column
{
	if (x > 7 || x < 0 || y > 7 || y < 0)
		return -1;
	if (value)
		big[x / 4] |= 1 << ((x % 4) * 8 + y);
	else
	 	big[x / 4] &= ~(1 << ((x % 4) * 8 + y));
	return 0;
}

int bc_getsetbigcharpos(int * big, int x, int y, int* value) // x - row, y - column
{
	if (x > 7 || x < 0 || y > 7 || y < 0)
		return -1;	
	else
		if (((big[x / 4] >> ((x % 4) * 8 + y)) & 0x1) == 1)
			*value = 1;
		else
			*value = 0;
	return 0;
}

int bc_bigcharwrite(int fd, int * big, int count)
{
	write(fd, big, sizeof(int) * 2 * count);
	close(fd);
	return 0;
}

int bc_bigcharread(int fd, int* big, int need_count, int* count)
{
	read(fd, big, sizeof(int) * 2 * need_count);
	close(fd);
	return 0;
}
