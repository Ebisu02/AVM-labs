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
const int commands[38] = {
			0xA,  0xB, 0x14, 0x15, 0x1E, 0x1F, 0x20, 0x21,
			0x28, 0x29, 0x2A, 0x2B, 0x33, 0x34, 0x35, 0x36,
			0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E,
			0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46,
			0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C };

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
	if (operand <= 0x7F)
	{
		if (std::binary_search(std::begin(commands), std::end(commands), command));
		{
			*value = (command << 7) | operand;
			return 0;
		}
		else
		{
			sc_regSet(INVALID_COMMAND, 1);
			return -1;
		}
	}
	else
	{
		return -1;
	}
}

int sc_commandDecode(int* command, int* operand, int value)
{
	int temp;

	if (((value >> 14) & 1) == 0)
	{
		temp = value >> 7;
		if (std::binary_search(std::begin(commands), std::end(commands), temp))
		{
			*command = temp;
			*operand = value & 0x7F;
			return 0;
		}
		else
		{
			sc_regSet(INVALID_COMMAND, 1);
			return -1;
		}
	}
	else
	{
		sc_regSet(INVALID_COMMAND, 1);
		return -1;
	}
}
