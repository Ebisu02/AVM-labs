#include "bc.h"

// `afgijklmnopqrstuvwxyz{|}~
// ◆▒°±␋┘┐┌└┼─├┤┴┬│≤≥π≠£·

int bc_printA(char * str) 
{
	cout << "\E(0" << str << "\E(B";
	return 0;
}

int bc_box(int r, int c, int w, int h) //
{
	mt_gotoxy(r, c);
	mt_setfgcolor(BLUE);
	char* t = new char[w + 2];
	for (int i = 1; i < w + 1; ++i)
	{
		t[i] = 'q';
	}
	
	t[0] = '1';
	t[w + 1] = 'k';
	bc_printA(t);
	
	char* t1 = new char[1];
	t1[0] = 'x';
	
	for (int i = r + 1; i < r + h + 1; ++i)
	{
		mt_gotoxy(i, c);
		bc_printA(t1);
		mt_gotoxy(i, c + w + 1);
		bc_printA(t1);
	}
	
	mt_gotoxy(h + r + 1, c);
	t[0] = 'm';
	t[w + 1] = 'j';
	bc_printA(t);
	mt_gotoxy(r + h + 2, c + w + 2);
	mt_setfgcolor(WHITE);
	return 0;
}

int bc_printbigchar(BIGCHAR chindex, int x, int y, COLORS color, COLORS color1) // x - row, y - column
{
	mt_setfgcolor(color1);
	char* t = new char[8];
	for (int i = 0, k = 0, ind = 0; i < 8; ++i)
	{
		if (i == 4)
		{
			ind = 1;
		}
		for (int j = 0; j < 8; ++j, ++k)
		{
			((bigchars[chindex][ind] >> k) & 0x1) == 0 ? t[j] = ' ' : t[j] = '`'; 
		}
		mt_gotoxy(x + i, y);
		bc_printA(t);
	}
	mt_setfgcolor(WHITE);
	mt_gotoxy(24, 0);
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
