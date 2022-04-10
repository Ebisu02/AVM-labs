#include <iostream>
#include <sstream>
#include <iomanip>
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "bc.h"
#include "myReadKey.h"

int counter = 0;
int cur_index = 0;

void print_interface()
{
	mt_clrscr();
	mt_setfgcolor(LIGHT_BLUE);
	std::cout << std::hex;
	mt_gotoxy(2, 1);
	mt_setfgcolor(LIGHT_BLUE);
	std::cout << ' ';
	for (int i = 0; i < 100; ++i)
	{
		mt_setfgcolor(LIGHT_BLUE);
		int cur_value;
		sc_memoryGet(i, cur_value);
		if ((i % 10 == 0) && (i != 0)) 
		{
			std::cout << "\n ";
		}
		if (counter == i) mt_setfgcolor(RED);
		if (((cur_value >> 14) & 1) == 0) std::cout << '+';
		else std::cout << '-';
		std::cout << setw(4) << std::setfill('0')  << '0' << ' ';
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
	int v = 0;
	sc_memoryGet(counter, v);
	if (((v >> 14) & 1) == 0) bc_printbigchar(PLUS, 14, 2, BLACK, BLUE);
	else bc_printbigchar(MINUS, 14, 2, BLACK, BLUE);
	bc_printbigchar((BIGCHAR)(
	(v >> 12) & 0b1111), 14, 11, BLACK, BLUE);
	bc_printbigchar((BIGCHAR)((v >> 8) & 0b1111), 14, 20, BLACK, BLUE);
	bc_printbigchar((BIGCHAR)((v >> 4) & 0b1111), 14, 29, BLACK, BLUE);
	bc_printbigchar((BIGCHAR)((v) & 0b1111), 14, 38, BLACK, BLUE);
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
	std::cout << "q - exit";
	mt_gotoxy(20, 76);
	std::cout << "F5 - accumulator";
	mt_gotoxy(21, 76);
	std::cout << "F6 - InstructionCounter";
	mt_gotoxy(22, 76);
	bc_box(13, 73, 26, 8);
	mt_gotoxy(36, 1);
	return;
}

void key_reset()
{
	sc_memoryInit();
	sc_regInit();
	counter = 0;
	print_interface();
	KEYS key = None;
}

void main_logic()
{
     	char* filename = "memory.bin";
	char* touch_command = "touch memory.bin";
	unsigned int flag;
	int index = 0;
	KEYS key = None;
	system(touch_command);
	print_interface();
	while(true)
	{
		counter = index;
		rk_readkey(key);
		switch(key)
		{
			case None: break;
			case Load: sc_memoryLoad(filename); print_interface(); break;
			case Save: sc_memorySave(filename); print_interface(); break;
			case Run: print_interface(); break;
			case Step: print_interface(); break;
			case Reset: key_reset(); print_interface(); break;
			case Accumulator: print_interface(); break;
			case InstructionCounter: print_interface(); break;
			case Down:  if (index < 90) index += 10; break;
			case Up: if (index > 9) index -= 10; break;
			case Left: if (index % 10 != 0) index -= 1; break;
			case Right: if (index % 10 != 9) index += 1; break;
			case CloseApplication: exit(1); break;
			default: break;
		}
		if (counter != index)
		{
			counter = index;
			print_interface();
		}
		
	}
}

int main()
{
	setbuf((stdout), 0);
	sc_memoryInit();
	sc_regInit();
	sc_regSet(CLOCK_PULSE_IGNORE, 1);
	sc_regSet(INVALID_COMMAND, 1);
	sc_regSet(OUT_OF_BOUNDS, 1);
	sc_regSet(DIVISION_BY_ZERO, 1);
	sc_regSet(SEGMENTATION_FAULT, 1);
	main_logic();
}
