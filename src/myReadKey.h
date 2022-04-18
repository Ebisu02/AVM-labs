#pragma once

#include <termios.h>
#include <cstdio>
#include <cstring>
#include <unistd.h>

using namespace std;

enum KEYS
{
	None,
	Load,
	Save,
	Run,
	Step,
	Reset,
	Accumulator,        // F5
	InstructionCounter, // F6
	Up,
	Down,
	Left,
	Right,
	CloseApplication,
	Enter,
};

int rk_readkey(KEYS &key);
int rk_mytermsave();
int rk_mytermrestore();
int rk_mytermregime(int regime, int vtime, int vmin, bool echo, bool sigint);
