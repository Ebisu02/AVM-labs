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
	mt_gotoxy(2, 2);
	for (int i = 0; i < 64; ++i)
	{
		int cur_value;
		sc_memoryGet(i, cur_value);
		if ((i % 10 == 0) && (i != 0)) std::cout << "\n";
		if (((cur_value >> 14) & 1) == 0) std::cout << "+";
		else std::cout << "-";
		std::cout << setw(4) << std::setfill('0') << cur_value << ' ';
		mt_setfgcolor(LIGHT_BLUE);
		//std::cout << "ABACABA";
	}
	//std::cout << "ABACABA";
	std::cout << std::dec;

	bc_box(1, 1, 10 * 6, 10);
	bc_box(1, 63, 20, 1);
	bc_box(4, 63, 20, 1);
	bc_box(7, 63, 20, 1);
	
	/* FLAGS */
	
	mt_gotoxy(11, 69);
	unsigned int temp_flag;
	
	sc_regGet(SEGMENTATION_FAULT, &temp_flag);
	temp_flag = 1 ? mt_setfgcolor(RED) : mt_setfgcolor(GREEN);
	std::cout << "O ";
	
	sc_regGet(DIVISION_BY_ZERO, &temp_flag);
	temp_flag = 1 ? mt_setfgcolor(RED) : mt_setfgcolor(GREEN);
	std::cout << "Z ";
	
	sc_regGet(OUT_OF_BOUNDS, &temp_flag);
	temp_flag = 1 ? mt_setfgcolor(RED) : mt_setfgcolor(GREEN);
	std::cout << "B ";
	
	sc_regGet(CLOCK_PULSE_IGNORE, &temp_flag);
	temp_flag = 1 ? mt_setfgcolor(RED) : mt_setfgcolor(GREEN);
	std::cout << "C ";
	
	sc_regGet(INVALID_COMMAND, &temp_flag);
	temp_flag = 1 ? mt_setfgcolor(RED) : mt_setfgcolor(GREEN);
	std::cout << "I ";
	
	mt_setfgcolor(WHITE);
	bc_box(10, 63, 20, 1);
	
	//big chars printing //
	bc_box(13, 1, 45, 8);
	bc_printbigchar(PLUS, 14, 2, BLACK, LIGHT_BLUE);
	bc_printbigchar(ZERO, 14, 11, BLACK, LIGHT_BLUE);
	bc_printbigchar(ZERO, 14, 20, BLACK, LIGHT_BLUE);
	bc_printbigchar(ZERO, 14, 29, BLACK, LIGHT_BLUE);
	bc_printbigchar(ZERO, 14, 38, BLACK, LIGHT_BLUE);
	int num_value_to_print = 0;
	sc_memoryGet(0, num_value_to_print);
	if (((num_value_to_print >> 14) & 1)  == 0)	bc_printbigchar(PLUS, 14, 2, BLACK, LIGHT_BLUE);
	else	bc_printbigchar(MINUS, 14, 2, BLACK, LIGHT_BLUE);
	
	bc_printbigchar((BIGCHAR)((num_value_to_print >> 12) & 0b1111), 14, 11, BLACK, LIGHT_BLUE);
	bc_printbigchar((BIGCHAR)((num_value_to_print >> 8) & 0b1111), 14, 20, BLACK, LIGHT_BLUE);
	bc_printbigchar((BIGCHAR)((num_value_to_print >> 4) & 0b1111), 14, 29, BLACK, LIGHT_BLUE);
	bc_printbigchar((BIGCHAR)(num_value_to_print & 0b1111), 14, 38, BLACK, LIGHT_BLUE);
	
	// info printing proccessing
	mt_setfgcolor(LIGHT_BLUE);
	
	mt_gotoxy(14, 50);
	std::cout << "1 == load";
	
	mt_gotoxy(15, 50);
	std::cout << "s == save";
	
	mt_gotoxy(16, 50);
	std::cout << "r = run";
	
	mt_gotoxy(17, 50);
	std::cout << "t = step";
	
	mt_gotoxy(18, 50);
	std::cout << "i == reset";
	
	mt_gotoxy(19, 50);
	std::cout << "f5 == accumulator";
	
	mt_gotoxy(20, 50);
	std::cout << "f6 == instruction counter";
	
	bc_box(13, 48, 35, 8);
	
	// names printing
	mt_setfgcolor(BLUE);
	mt_gotoxy(1, 25);
	std::cout << "Memory ";
	
	mt_gotoxy(1, 67);
	
	//accumulator
	std::cout << "Accumulator ";
	mt_gotoxy(2, 71);
	mt_setfgcolor(LIGHT_BLUE);
	
	//sc_memoryGet(cur_index, accumulator)
	//if ((accumulator >> 14) & 1) == 0) '+'
	//else '-'
	
	std::cout << "+";
	std::cout << std::hex << setw(4) << std::setfill('0') << /*accumulator*/ 1 << std::dec;
	mt_setfgcolor(BLUE);
	
	// instr counter printing
	mt_gotoxy(4, 64);
	std::cout << "Instruction counter ";
	mt_gotoxy(5, 71);
	mt_setfgcolor(LIGHT_BLUE);
	std::cout << '+' << std::dec << setw(4) << std::setfill('0') << /*instr counter*/ 1 << std::dec;
	
	mt_setfgcolor(BLUE);
	mt_gotoxy(7, 68);
	std::cout << " Operation ";
	
	mt_gotoxy(10, 70);
	std::cout << " Flags ";
	
	mt_gotoxy(13, 60);
	std::cout << " Keyboard ";
	
	std::cout << "\n\n\n\n\n\n\n\n\n\n";
	mt_gotoxy(24, 1);
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
