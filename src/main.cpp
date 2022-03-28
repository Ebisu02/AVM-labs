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
		mt_setfgcolor(LIGHT_BLUE);
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
	
	//big chars printing //
	//bc_box(13, 1, 45, 8);
	bc_printbigchar(ZERO, 14, 2, BLACK, BLUE);
	bc_printbigchar(ONE, 14, 11, BLACK, BLUE);
	bc_printbigchar(TWO, 14, 20, BLACK, BLUE);
	bc_printbigchar(THREE, 14, 29, BLACK, BLUE);
	bc_printbigchar(FOUR, 14, 38, BLACK, BLUE);
	bc_printbigchar(FIVE, 14, 47, BLACK, BLUE);
	bc_printbigchar(SIX, 14, 56, BLACK, BLUE);
	bc_printbigchar(SEVEN, 14, 65, BLACK, BLUE);
	bc_printbigchar(EIGHT, 14, 74, BLACK, BLUE);
	bc_printbigchar(NINE, 14, 83, BLACK, BLUE);
	bc_printbigchar(A, 25, 2, BLACK, BLUE);
	bc_printbigchar(B, 25, 11, BLACK, BLUE);
	bc_printbigchar(C, 25, 20, BLACK, BLUE);
	bc_printbigchar(D, 25, 29, BLACK, BLUE);
	bc_printbigchar(E, 25, 38, BLACK, BLUE);
	bc_printbigchar(F, 25, 47, BLACK, BLUE);
	bc_printbigchar(PLUS, 25, 56, BLACK, BLUE);
	bc_printbigchar(MINUS, 25, 65, BLACK, BLUE);
	bc_printbigchar(K, 25, 74, BLACK, BLUE);
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
	print_interface();
	
}
