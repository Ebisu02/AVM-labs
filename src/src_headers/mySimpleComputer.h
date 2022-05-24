/*
#pragma once


#include "mySimpleComputer.cpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define SEGMENTATION_FAULT 1
#define DIVISION_BY_ZERO 2
#define OUT_OF_BOUNDS 3
#define CLOCK_PULSE_IGNORE 4
#define INVALID_COMMAND 5

using namespace std;

char Path[] = "memory.bin";
int memory[100];
const int commands[38] = {
                        0xA,  0xB, 0x14, 0x15, 0x1E, 0x1F, 0x20, 0x21,
                        0x28, 0x29, 0x2A, 0x2B, 0x33, 0x34, 0x35, 0x36,
                        0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E,
                        0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46,
                        0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C };
*/
// 1 - "p" - segmentation fault
// 2 - "0" - error of deleting on null
// 3 - "M" - error out of memory
// 4 - "T" - ignoring tact impulses
// 5 - "E" - invalid command
#pragma once

#include "msc.h"

#define SEGMENTATION_FAULT 1
#define DIVISION_BY_ZERO 2
#define OUT_OF_BOUNDS 3
#define CLOCK_PULSE_IGNORE 4
#define INVALID_COMMAND 5

inline const int commands[38] = {0xA,  0xB,  0x14, 0x15, 0x1E, 0x1F,
                                 0x20, 0x21, // READ, WRITE, ADD, SUB, DIV, MUL,
                                             // LOAD, STORE
                                 0x28, 0x29, 0x2A, 0x2B, 0x33, 0x34,
                                 0x35, 0x36, // JUMP, JNEG, JZ, HALT, MOVA, =
                                 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C,
                                 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42,
                                 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
                                 0x49, 0x4A, 0x4B, 0x4C};

inline const char Path[] = "memory.bin";

using namespace std;

int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int &value);
int sc_memorySave(char *filename);
int sc_memoryLoad(char *filename);
int sc_regInit(void);
int sc_regSet(int reg, int value);
int sc_regGet(int reg, unsigned int *value);
int sc_commandEncode(int str_num, string command, int operand);
int sc_commandDecode(string &command, int &operand, int value);
