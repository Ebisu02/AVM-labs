#pragma once
#include "assembler.h"
#include "bc.h"
#include "myReadKey.h"
#include "myTerm.h"
#include "mySimpleComputer.h"
using namespace std;

void print_interface();
void key_reset();
void key_run();
void set_timer(long time);
void signal_handling_process(int signal);
void key_step();
void signal_reset(int signal);
void main_logic();
int get_value_by_counter();
void set_accumulator(int value);
void set_counter(int value);