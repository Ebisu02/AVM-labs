#include "assembler.h"
#include "msc.h"
#include <iostream>

int sas_read(int address)
{
	if (address < 0 || address > 99)
	{
		// Segmentation fault
		return 1;
	}
	int value;
	std::cout << "\nPlease enter a value for memory cell #" << address << " - ";
	std::cin >> value;
	value %= 10000;
	sc_memorySet(address, value);
	return 0; // is ok
}

int sas_write(int address)
{
	if (address < 0 || address > 99)
	{
		// Segmentation fault
		return 1;
	}
	int value;
	sc_memoryGet(address, value);
	std::cout << "\nValue in memory cell #" << address << " - " << value;
}

int sas_load(int address)
{
	int value = 0;
	sc_memoryGet(address, value);
	set_accumulator(value);
	return 0; // is ok
}

int sas_store(int accumulator, int address)
{
	sc_memorySet(address, accumulator);
	return 0; // is ok
}

int sas_add(int accumulator, int address)
{
	int v1, res;
	sc_memoryGet(address, v1);
	res = v1 + accumulator;
	res %= 10000;
	set_accumulator(res);
	return 0; // is ok
}

int sas_sub(int accumulator, int address)
{
	int v1, res;
	sc_memoryGet(address, v1);
	res = accumulator - v1;
	res %= 10000;
	set_accumulator(res);
	return 0; // is ok
}

int sas_div(int accumulator, int address)
{
	int v1, res;
	sc_memoryGet(address, v1);
	res = accumulator / v1;
	res %= 10000;
	set_accumulator(res);
	return 0; // is ok
}

int sas_mul(int accumulator, int address)
{
	int v1, res;
	sc_memoryGet(address, v1);
	res = accumulator * v1;
	res %= 10000;
	set_accumulator(res);
	return 0; // is ok
}

int sas_jump(int address)
{
	set_counter(address);
	return 0; // is ok
}

int sas_jneg(int accumulator, int address)
{
	if (accumulator < 0)
	{
		set_counter(address);
	}
	return 0;
}

int sas_jz(int accumulator, int address)
{
	if (accumulator == 0)
	{
		set_counter(address);
	}
	return 0;
}

int sas_halt()
{
	return -1; // signal to end assembler code
}

int mova(int address, int accumulator)
{
	int v1;
	sc_memoryGet(address, v1);
	sc_memorySet(accumulator, v1);
	sc_memorySet(address, 0);
	return 0; // is ok?
}