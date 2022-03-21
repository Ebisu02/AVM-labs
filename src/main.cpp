#include "mySimpleComputer.h"
#include "myTerm.h"
#include "bc.h"

void print_interface()
{
	mt_clear_screen();
	
	mt_setfgcolor(YELOWW);
	std::cout << std::hex;
	mt_gotoxy(2, 2);
	for (int i = 0; i < 100; ++i)
	{
		int cur_value;
		sc_memoryGet(i, &cur_value);
		if ((i % 10 == 0) && (i != 0)) std::cout << "\n";
		if ((cur_value >> 14) & 1) == 0) std::cout << "+";
		else std::cout << "-";
		std::cout << std::setw(4) << std::setfill('0') << cur_value << ' ';
	}
	std::cout << std::dec;
	bc_box(1, 1, 10 * 6, 10);
	bc_box(1, 63, 20, 1);
	bc_box(4, 63, 20, 1);
	bc_box(7, 63, 20, 1);
	
	/* FLAGS */
	
	mt_gotoxy(11, 69);
	unsigned int temp_flag;
	sc_regGet(SEGMENTATION_FAULT, temp_flag);
	
}

int main()
{
	string touch_command = "touch "; touch_command += Path;
	system(touch_command.c_str());
	sc_memoryInit();
	sc_regInit();
	sc_regSet(CLOCK_PULSE_IGNORE, 1);
	
	
	
	
}
