#pragma once

#include <iostream>
#include <fstream>
#include "msc.h"

using namespace std;

/*enum simple_assembler_commands{
	READ, // 
	WRITE, //
	LOAD, // write in accumulator value from address
	STORE, // read from accumulator by address
	ADD, // + from accumulator witn address in accum
	SUB, // - from accumulator witn address in accum
	DIVIDE, // : from accumulator witn address in accum
	MUl, // * from accumulator witn address in accum
	JUMP, // goto address
	JNEG, // goto address if in accumulator neg num
	JZ, // goto address if in accumulator null
	HALT, // Get end of programm
	MOVA // Get value from address and write it in address what we have in accumulator  
};*/


int sas_read(int address); // 10
int sas_write(int address); // 11
int sas_load(int address); // 20
int sas_store(int accumulator, int address); // 21
int sas_add(int accumulator, int address); // 30
int sas_sub(int accumulator, int address); // 31
int sas_div(int accumulator, int address); // 32
int sas_mul(int accumulator, int address); // 33
int sas_jump(int address); // 40
int sas_jneg(int accumulator, int address); // 41
int sas_jz(int accumulator, int address); // 42
int sas_halt(); // 43
int sas_mova(int address, int accumulator); // 71
void sas_manager(string path_to_file);