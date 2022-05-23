#pragma once

#include "msc.h"

using namespace std;

void sb_input(string name);
void sb_print(string name);
void sb_goto(string link);
void sb_if(string left_value, string cond, string right_value, string command);
void sb_let(string name, string left_v, string sign, string right_v);
void sb_end();
void sb_manager();
string toString(int val);