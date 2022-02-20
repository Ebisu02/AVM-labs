#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define SEGMENTATION_FAULT 1
#define DIVISION_BY_ZERO 2
#define OUT_OF_BOUNDS 3
#define CLOCK_PULSE_IGNORE 4
#define INVALID_COMMAND 5

using namespace std;

const char Path[] = "memory.bin";
int memory[100];
int commands[38] = { 0xA, 0xB, 0x;
unsigned int flags = 0b00000;
// 1 - "p" - segmentation fault
// 2 - "0" - error of deleting on null
// 3 - "M" - error out of memory
// 4 - "T" - ignoring tact impulses
// 5 - "E" - invalid command

int sc_memoryInt()
{
	for (int i = 0; i < 100; ++i)
	{
		memory[i] = 0;
	}
	return 0;
}

int sc_memorySet(int address, int value)
{
	if (address >= 0 && address < 100)
	{
		memory[address] = value;
		return 0;	
	}
	else 
	{
		flags = flags | (1 << (1 - 1));
		return printf("\nError: Segmentation fault\n");
	}
}

int sc_memoryGet(int address, int * value)
{
	if (address >= 0 && address < 100)
	{
		value = memory[address];
	}
	else 
	{
		flags = flags | (1 << (1 - 1));
		return printf("\nError: Segmentation fault\n);
	}
}

int sc_memorySave(char * filename)
{
	FILE* file = nullptr;
	
	file = fopen(Path, "wb");
	if (file == nullptr)
	{
		flags = flags | (1 << (1 - 1));
		fclose(file);
		return printf("\nError: Segmentation fault(invalid open file)\n);
	}
	else
	{
		fwrite(memory, sizeof(int), 100, file);
		fclose(file);
	}
	return 0;
}

int sc_memoryLoad(char * filename)
{
	FILE* file = nullptr;
	
	file = fopen(Path, "rb");
	if (file == nullptr)
	{
		flags = flags | (1 << 1);
		fclose(file);
		return printf("\nError: Segmentation fault(invalid open file)\n);
	}
	else
	{
		fread(memory, sizeof(int), 100, file);
		fclose(file);
	}
	
	return 0;
}

int sc_regInit(void)
{
	for (int i = 1; i <= 5; ++i)
	{
		flags = flags & (~(1 << k));
	}
	return 0;
}

int sc_regSet(int register, int value)
{
	if ((register > 5) || (register < 1)) 
	{
		return -1;
	}
	if (value)
	{
		flags |= (1 << register);
	}
	else
	{
		flags &= (~(1 << register));
	}
	return 0;
}

int sc_regGet(int register, unsigned int* value)
{
	if ((register >= 5) || (register <= 1))
	{
		return -1;
	}
	*value = ((flags >> register) & 0x1);
	return 0;
}

int sc_commandEncode(int command, int operand, int * value)
{
	
	return 0;
}

