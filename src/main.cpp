#include <iostream>
#include <sstream>
#include <iomanip>
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "bc.h"

void print_interface()
{
	mt_clrscr();
	mt_setfgcolor(LIGHT_BLUE);
	std::cout << std::hex;
	mt_gotoxy(2, 1);
	for (int i = 0; i < 100; ++i)
	{
		int cur_value;
		sc_memoryGet(i, cur_value);
		if ((i % 10 == 0) && (i != 0))
		{
			std::cout << "\n";
		}
		std::cout << " +" << setw(4) << std::setfill('0') << cur_value << ' ';
		//mt_setfgcolor(LIGHT_BLUE);
		//std::cout << "ABACABA";
	}
	//std::cout << "ABACABA";
	std::cout << std::dec;


	bc_box(1, 1, 10 * 7, 10);
	bc_box(1, 73, 40, 1);
	bc_box(4, 73, 40, 1);
	bc_box(7, 73, 40, 1);
	
	/* FLAGS */
	
	mt_gotoxy(11, 79);
	unsigned int tFlag;
	sc_regGet(SEGMENTATION_FAULT, &tFlag);
	tFlag == 1 ? mt_setfgcolor(RED) : mt_setfgcolor(GREEN);
	std::cout << "0 ";
	sc_regGet(DIVISION_BY_ZERO, &tFlag);
	tFlag == 1 ? mt_setfgcolor(RED) : mt_setfgcolor(GREEN);
	std::cout << "Z ";
	sc_regGet(OUT_OF_BOUNDS, &tFlag);
	tFlag == 1 ? mt_setfgcolor(RED) : mt_setfgcolor(GREEN);
	std::cout << "B ";
	sc_regGet(CLOCK_PULSE_IGNORE, &tFlag);
	tFlag == 1 ? mt_setfgcolor(RED) : mt_setfgcolor(GREEN);
	std::cout << "C ";
	sc_regGet(INVALID_COMMAND, &tFlag);
	tFlag == 1 ? mt_setfgcolor(RED) : mt_setfgcolor(GREEN);
	std::cout << "I ";
	mt_setfgcolor(WHITE);
	bc_box(10, 73, 20, 1);
	
	//big chars printing //
	
	//bc_box(13, 1, 45, 8);
	bc_printbigchar(PLUS, 14, 2, BLACK, BLUE);
	bc_printbigchar(ZERO, 14, 11, BLACK, BLUE);
	bc_printbigchar(ZERO, 14, 20, BLACK, BLUE);
	bc_printbigchar(ZERO, 14, 29, BLACK, BLUE);
	bc_printbigchar(ZERO, 14, 38, BLACK, BLUE);
	bc_printbigchar(ZERO, 14, 47, BLACK, BLUE);
	
	// info
	mt_setfgcolor(LIGHT_BLUE);
	mt_gotoxy(14, 76);
	std::cout << "l - load";
	mt_gotoxy(15, 76);
	std::cout << "s - save";
	mt_gotoxy(16, 76);
	std::cout << "r - run";
	mt_gotoxy(17, 76);
	std::cout << "t - step";
	mt_gotoxy(18, 76);
	std::cout << "i - reset";
	mt_gotoxy(19, 76);
	bc_box(13, 73, 13, 7);
	mt_gotoxy(36, 1);
	return;
}

int main()
{
	string touch_command = "touch "; touch_command += Path;
	system(touch_command.c_str());
	sc_memoryInit();
	sc_regInit();
	sc_regSet(CLOCK_PULSE_IGNORE, 1);
	sc_regSet(INVALID_COMMAND, 1);
	sc_regSet(OUT_OF_BOUNDS, 1);
	sc_regSet(DIVISION_BY_ZERO, 1);
	sc_regSet(SEGMENTATION_FAULT, 1);
	print_interface();	
}
