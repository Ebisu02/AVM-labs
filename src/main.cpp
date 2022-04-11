#include <iostream>
#include <sstream>
#include <iomanip>
#include <sys/time.h>
#include <signal.h>
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "bc.h"
#include "myReadKey.h"

int counter = 0;
int cur_index = 0;
int accumulator = 0;

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
		std::cout << setw(4) << std::setfill('0')  << cur_value << ' ';
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
	int v = 0;
	sc_memoryGet(counter, v);
	if (((v >> 14) & 1) == 0) bc_printbigchar(PLUS, 14, 2, BLACK, BLUE);
	else bc_printbigchar(MINUS, 14, 2, BLACK, BLUE);
	bc_printbigchar((BIGCHAR)((v >> 12) & 0b1111), 14, 11, BLACK, BLUE);
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

	//names
	mt_setfgcolor(BLUE);
	mt_gotoxy(1,25);
	std::cout << " Memory ";
	mt_gotoxy(1, 85);
	std::cout << " Accumulator ";
	mt_gotoxy(2, 90);
	sc_memoryGet(cur_index, accumulator);
	mt_setfgcolor(YELLOWW);
	if (((accumulator >> 14) & 1) == 0) std::cout << '+';
	else std::cout << '-';
	std::cout << std::hex << std::setw(4) << std::setfill('0') << accumulator << std::dec;
	mt_setfgcolor(BLUE);
	mt_gotoxy(4, 82);
	std::cout << " Instruction Counter ";
	mt_gotoxy(5, 90);
	mt_setfgcolor(YELLOWW);
	std::cout << std::dec << setw(2) << std::setfill('0') << counter << std::dec;
	mt_setfgcolor(BLUE);
	mt_gotoxy(7, 85);
	std::cout << " Operation ";
	mt_gotoxy(36, 1);
	return;
}

void key_reset()
{
	sc_memoryInit();
	counter = cur_index = 0;
	sc_regInit();
	sc_regSet(CLOCK_PULSE_IGNORE, true);
	print_interface();
}

void key_run()
{
	sc_regSet(CLOCK_PULSE_IGNORE, false);
	KEYS key = None;
	unsigned int tf1, tf2;
	sc_regGet(CLOCK_PULSE_IGNORE, &tf1);
	sc_regGet(OUT_OF_BOUNDS, &tf2);
	while (tf1 == 0 && tf2 == 0)
	{
		mt_clrscr();
		print_interface();
		cur_index = counter;
		pause();
		rk_readkey(key);
		print_interface();
		if (counter >= 99 || key == Reset)
		{
			raise(SIGUSR1);
			break;
		}
		sc_regGet(CLOCK_PULSE_IGNORE, &tf1);
		sc_regGet(OUT_OF_BOUNDS, &tf2);
		fflush(stdout);		
	}
}

void set_timer(long time)
{
	itimerval nval, oval;
	nval.it_interval.tv_sec = time;
	nval.it_interval.tv_usec = 0;
	nval.it_value.tv_sec = 1;
	nval.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &nval, &oval);
}

void signal_handling_process(int signal)
{
	unsigned int v1, v2;
	sc_regGet(CLOCK_PULSE_IGNORE, &v1);
	sc_regGet(OUT_OF_BOUNDS, &v2);
	if (v1 == 0 && v2 == 0)
	{
		counter++;
		cur_index = counter;
		mt_clrscr();
		print_interface();
	}
	else if (v2 == 1)
	{
		key_reset();
		print_interface();
	}
}

void signal_reset(int signal)
{
	key_reset();
}

void main_logic()
{
     	char* filename = "memory.bin";
	char* touch_command = "touch memory.bin";
	sc_regSet(CLOCK_PULSE_IGNORE, true);
	counter = 0;
	signal(SIGALRM, signal_handling_process);
	signal(SIGUSR1, signal_reset);
	KEYS key = None;
	system(touch_command);
	unsigned int tf;
	sc_regGet(CLOCK_PULSE_IGNORE, &tf);
	print_interface();
	while(key != CloseApplication && tf == 1)
	{
		rk_readkey(key);
		switch(key)
		{
			case None: break;
			case Load: sc_memoryLoad(filename); print_interface(); break;
			case Save: sc_memorySave(filename); print_interface(); break;
			case Run: key_run(); print_interface(); break;
			case Step: print_interface(); break;
			case Reset: key_reset(); print_interface(); break;
			case Accumulator: int v; mt_setfgcolor(YELLOWW); mt_gotoxy(24, 2); std::cout << "Input: ";
					  std::cin >> std::hex >> v; mt_setfgcolor(BLUE);
					  sc_memorySet(counter, v); print_interface(); break;
			case InstructionCounter: print_interface(); break;
			case Down:  if (cur_index < 90) cur_index += 10; break;
			case Up: if (cur_index > 9) cur_index -= 10; break;
			case Left: if (cur_index % 10 != 0) cur_index -= 1; break;
			case Right: if (cur_index % 10 != 9) cur_index += 1; break;
			case CloseApplication: exit(1); break;
			default: break;
		}
		if (counter != cur_index)
		{
			counter = cur_index;
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
