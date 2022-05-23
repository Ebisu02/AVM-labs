#include "../src_headers/mySimpleComputer.h"

// 1 - "p" - segmentation fault
// 2 - "0" - error of deleting on null
// 3 - "M" - error out of memory
// 4 - "T" - ignoring tact impulses
// 5 - "E" - invalid command

int memory[100];
unsigned int flags = 0;

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

int sc_memoryGet(int address, int& value)
{
	if (address >= 0 && address < 100)
	{
		value = memory[address];
	}
	else 
	{
		flags = flags | (1 << (1 - 1));
		return printf("\nError: Segmentation fault\n");
	}
	return 0; 
}

int sc_memorySave(char * filename)
{
	FILE* file = nullptr;
	
	file = fopen(Path, "wb");
	if (file == nullptr)
	{
		flags = flags | (1 << (1 - 1));
		fclose(file);
		return printf("\nError: Segmentation fault(invalid open file)\n");
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
		return printf("\nError: Segmentation fault(invalid open file)\n");
	}
	else
	{
		fread(memory, sizeof(int), 100, file);
		fclose(file);
	}
	
	return 0;
}

int sc_regInit()
{
	flags = 0;
	return 0;
}

int sc_regSet(int reg, int value)
{
	if ((reg > 5) || (reg < 0)) 
	{
		return -1;
	}
	if (value)
	{
		flags |= (1 << reg);
	}
	else
	{
		flags &= (~(1 << reg));
	}
	return 0;
}

int sc_regGet(int reg, unsigned int* value)
{
	if ((reg > 5) || (reg < 0))
	{
		return -1;
	}
	*value = ((flags >> reg) & 0x1);
	return 0;
}

int sc_commandEncode(int str_num, string command, int operand)
{
	int command_code;
	if (command == "READ")
	{
		command_code = commands[0];
	}
	else if (command == "WRITE")
	{
		command_code = commands[1];
	}
	else if (command == "ADD")
	{
		command_code = commands[2];
	}
	else if (command == "SUB")
	{
		command_code = commands[3];
	}
	else if (command == "DIV")
	{
		command_code = commands[4];
	}
	else if (command == "MUL")
	{
		command_code = commands[5];
	}
	else if (command == "LOAD")
	{
		command_code = commands[6];
	}
	else if (command == "STORE")
	{
		command_code = commands[7];
	}
	else if (command == "JUMP")
	{
		command_code = commands[8];
	}
	else if (command == "JNEG")
	{
		command_code = commands[9];
	}
	else if (command == "JZ")
	{
		command_code = commands[10];
	}
	else if (command == "HALT")
	{
		command_code = commands[11];
	}
	else if (command == "MOVA")
	{
		command_code = commands[12];
	}
	else
	{
		sc_regSet(INVALID_COMMAND, 1);
		return -1;
	}
	int value_to_write = (command_code << 7) | operand;
	sc_memorySet(str_num, value_to_write);
	return 0;
}

int sc_commandDecode(string& command, int& operand)
{
/*	int temp;

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
	}*/
}
