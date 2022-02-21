#include "mySimpleComputer.h"

int sc_memoryInit()
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
