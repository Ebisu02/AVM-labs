#include "../src_headers/msc.h"

int main()
{
	set_timer(1);
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
