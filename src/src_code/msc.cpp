#include "../src_headers/msc.h"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <signal.h>
#include <sstream>
#include <string.h>
#include <sys/time.h>

int counter = 0;
int cur_index = 0;
int accumulator = 0;

bool is_file_exist(string path_to_file) {
  // std::cout << file.is_open();
  if (std::filesystem::exists(path_to_file)) {
    return true;
  }
  return false;
}

void set_counter(int value) {
  if (value <= 99 && value >= 0) {
    counter = value;
  }
}

int get_accumulator() { return accumulator; }

void set_accumulator(int value) { accumulator = value; }

int get_value_by_counter() {
  int value = 0;
  sc_memoryGet(value, counter);
  return value;
}

void print_interface() {
  mt_clrscr();
  mt_setfgcolor(LIGHT_BLUE);
  std::cout << std::hex;
  mt_gotoxy(2, 1);
  mt_setfgcolor(LIGHT_BLUE);
  std::cout << ' ';
  for (int i = 0; i < 100; ++i) {
    mt_setfgcolor(LIGHT_BLUE);
    int cur_value;
    sc_memoryGet(i, cur_value);
    if ((i % 10 == 0) && (i != 0)) {
      std::cout << "\n ";
    }
    if (counter == i)
      mt_setfgcolor(RED);
    if (((cur_value >> 14) & 1) == 0)
      std::cout << '+';
    else
      std::cout << '-';
    std::cout << setw(4) << std::setfill('0') << cur_value << ' ';
    mt_setfgcolor(LIGHT_BLUE);
    // std::cout << "ABACABA";
  }
  // std::cout << "ABACABA";
  std::cout << std::dec;

  bc_box(1, 1, 10 * 7, 10);
  bc_box(1, 73, 40, 1);
  bc_box(4, 73, 40, 1);
  bc_box(7, 73, 40, 1);

  /* FLAGS */

  mt_gotoxy(11, 79);
  unsigned int tFlag;
  sc_regGet(SEGMENTATION_FAULT, &tFlag);
  tFlag == 1 ? mt_setfgcolor(RED) : mt_setfgcolor(RED);
  std::cout << "0 ";
  sc_regGet(DIVISION_BY_ZERO, &tFlag);
  tFlag == 1 ? mt_setfgcolor(RED) : mt_setfgcolor(RED);
  std::cout << "Z ";
  sc_regGet(OUT_OF_BOUNDS, &tFlag);
  tFlag == 1 ? mt_setfgcolor(RED) : mt_setfgcolor(RED);
  std::cout << "B ";
  sc_regGet(CLOCK_PULSE_IGNORE, &tFlag);
  tFlag == 1 ? mt_setfgcolor(WHITE) : mt_setfgcolor(GREEN);
  std::cout << "C ";
  sc_regGet(INVALID_COMMAND, &tFlag);
  tFlag == 1 ? mt_setfgcolor(WHITE) : mt_setfgcolor(GREEN);
  std::cout << "I ";
  bc_box(10, 73, 20, 1);

  // big chars printing //

  // bc_box(13, 1, 45, 8);
  int v = 0;
  sc_memoryGet(counter, v);
  if (((v >> 14) & 1) == 0)
    bc_printbigchar(PLUS, 14, 2, BLACK, BLUE);
  else
    bc_printbigchar(MINUS, 14, 2, BLACK, BLUE);
  bc_printbigchar((BIGCHAR)((v >> 12) & 0b1111), 14, 11, BLACK, BLUE);
  bc_printbigchar((BIGCHAR)((v >> 8) & 0b1111), 14, 20, BLACK, BLUE);
  bc_printbigchar((BIGCHAR)((v >> 4) & 0b1111), 14, 29, BLACK, BLUE);
  bc_printbigchar((BIGCHAR)((v)&0b1111), 14, 38, BLACK, BLUE);
  // info
  mt_setfgcolor(LIGHT_BLUE);
  mt_gotoxy(14, 76);
  std::cout << "l - load";
  mt_gotoxy(15, 76);
  std::cout << "s - save";
  mt_gotoxy(16, 76);
  std::cout << "r - run";
  mt_gotoxy(17, 76);
  std::cout << "t - step";
  mt_gotoxy(18, 76);
  std::cout << "i - reset";
  mt_gotoxy(19, 76);
  std::cout << "q - exit";
  mt_gotoxy(20, 76);
  std::cout << "F5 - accumulator";
  mt_gotoxy(21, 76);
  std::cout << "F6 - InstructionCounter";
  mt_gotoxy(22, 76);
  std::cout << "F7 - compile asm";
  mt_gotoxy(23, 76);
  std::cout << "F8 - compile basic";
  bc_box(13, 73, 26, 10);

  // names
  mt_setfgcolor(BLUE);
  mt_gotoxy(1, 25);
  std::cout << " Memory ";
  mt_gotoxy(1, 85);
  std::cout << " Accumulator ";
  mt_gotoxy(2, 90);
  mt_setfgcolor(YELLOWW);
  if (((accumulator >> 14) & 1) == 0)
    std::cout << '+';
  else
    std::cout << '-';
  std::cout << std::hex << std::setw(4) << std::setfill('0') << accumulator
            << std::dec;
  mt_setfgcolor(BLUE);
  mt_gotoxy(4, 82);
  std::cout << " Instruction Counter ";
  mt_gotoxy(5, 90);
  mt_setfgcolor(YELLOWW);
  std::cout << std::dec << setw(2) << std::setfill('0') << counter;
  mt_setfgcolor(BLUE);
  mt_gotoxy(7, 85);
  std::cout << " Operation ";
  mt_gotoxy(8, 90);
  mt_setfgcolor(YELLOWW);
  int v4 = 0;
  string cmd;
  int v5 = 0;
  int v6 = 0;
  sc_memoryGet(cur_index, v6);
  v4 = sc_commandDecode(cmd, v5, v6);
  if (v4 != 0) {
    std::cout << std::hex << v4 << std::dec;
  }
  mt_setfgcolor(BLUE);
  mt_gotoxy(24, 2);
  return;
}

void key_reset() {
  sc_memoryInit();
  counter = cur_index = 0;
  accumulator = 0;
  sc_regInit();
  sc_regSet(CLOCK_PULSE_IGNORE, true);
  print_interface();
}

void key_run() {
  sc_regSet(CLOCK_PULSE_IGNORE, false);
  KEYS key = None;
  unsigned int tf1, tf2;
  sc_regGet(CLOCK_PULSE_IGNORE, &tf1);
  int i = 0;
  sc_regGet(OUT_OF_BOUNDS, &tf2);
  while (tf1 == 0 && tf2 == 0) {
    string command;
    int operand;
    int value;
    sc_memoryGet(cur_index, value);
    sc_commandDecode(command, operand, value);
    if (command == "READ") {
      sas_read(operand);
    }
    mt_clrscr();
    print_interface();
    cur_index = counter;
    pause();
    rk_readkey(key);
    print_interface();
    if (counter >= 100 || key == Reset) {
      raise(SIGUSR1);
      break;
    }
    sc_regGet(CLOCK_PULSE_IGNORE, &tf1);
    sc_regGet(OUT_OF_BOUNDS, &tf2);
    fflush(stdout);
  }
}

void set_timer(long time) {
  itimerval nval, oval;
  nval.it_interval.tv_sec = time;
  nval.it_interval.tv_usec = 0;
  nval.it_value.tv_sec = 1;
  nval.it_value.tv_usec = 0;
  setitimer(ITIMER_REAL, &nval, &oval);
}

void signal_handling_process(int signal) {
  unsigned int v1, v2;
  sc_regGet(CLOCK_PULSE_IGNORE, &v1);
  sc_regGet(OUT_OF_BOUNDS, &v2);
  if (v1 == 0 && v2 == 0) {
    counter++;
    cur_index = counter;
    mt_clrscr();
    print_interface();
  } else if (v2 == 1) {
    key_reset();
    print_interface();
  }
}

void key_step() {
  if (cur_index <= 99) {
    string command;
    int operand;
    int value;
    sc_memoryGet(cur_index, value);
    sc_commandDecode(command, operand, value);
    if (command == "READ") {
      sas_read(operand);
    } else if (command == "WRITE") {
      sas_write(operand);
    } else if (command == "LOAD") {
      sas_load(operand);
    } else if (command == "STORE") {
      sas_store(get_accumulator(), operand);
    } else if (command == "=") {
      sas_equals(cur_index, operand);
    } else if (command == "ADD") {
      sas_add(get_accumulator(), operand);
    } else if (command == "SUB") {
      sas_sub(get_accumulator(), operand);
    } else if (command == "MUL") {
      sas_mul(get_accumulator(), operand);
    } else if (command == "DIV") {
      sas_div(get_accumulator(), operand);
    } else if (command == "JUMP") {
      sas_jump(operand);
    } else if (command == "JNEG") {
      sas_jneg(get_accumulator(), operand);
    } else if (command == "JZ") {
      sas_jz(get_accumulator(), operand);
    } else if (command == "HALT") {
      sas_halt();
    }
    ++cur_index;
    return;
  }
  cur_index = 0;
}

void signal_reset(int signal) { key_reset(); }

void key_enter() {
  int v2;
  mt_setfgcolor(YELLOWW);
  mt_gotoxy(24, 2);
  std::cout << "Input: ";
  std::cin >> v2;
  v2 %= 10000;
  mt_setfgcolor(BLUE);
  sc_memorySet(counter, v2);
  print_interface();
}

void key_compile_asm() {
  string path;
  string path_o;
  mt_setfgcolor(YELLOWW);
  mt_gotoxy(26, 2);
  std::cout << "Please make sure that ur [name].sa simple assembler script in "
               "directory scripts/asm/\n"
            << " and then enter a name of this file (Ex.: name for "
               "'scripts/asm/asm1.sa' is 'asm1'\n Input: ";
  std::cin >> path;

  path_o = "../scripts/asm/obj/" + path + ".o";
  path = "../scripts/asm/" + path + ".msa";
  string tch_cmd = "touch " + path_o;
  system(tch_cmd.c_str());
  if (is_file_exist(path)) {
    mt_gotoxy(29, 2);
    std::cout << path_o;
    sas_manager(path, path_o);
  } else {
    mt_gotoxy(29, 2);
    std::cout << "Error: invalid path to file";
  }
}

void key_compile_basic()
{
    string path, path_o, path_asm;
    mt_setfgcolor(YELLOWW);
    mt_gotoxy(26, 2);
    std::cout << "Please make sure that ur [name].sa simple assembler script in "
        "directory scripts/asm/\n"
        << " and then enter a name of this file (Ex.: name for "
        "'scripts/basic/sb1.sb' is 'sb1'\n Input: ";
    std::cin >> path;
    path_o = "../scripts/basic/asm/obj/" + path + ".o";
    path_asm = "../scripts/basic/asm/" + path + ".msa";
    path = "../scripts/basic/" + path + ".sb";
    string tch_cmd1 = "touch " + path_o;
    string tch_cmd2 = "touch " + path_asm;
    system(tch_cmd1.c_str());
    system(tch_cmd2.c_str());
    if (is_file_exist(path))
    {
        mt_gotoxy(29, 2);
        std::cout << path_o;
        sb_manager(path, path_asm, path_o);
    }
    else
    {
        mt_gotoxy(29, 2);
        std::cout << "Error: invalid path to file";
    }
}

void key_instructionCounter() {
  int v3;
  mt_setfgcolor(YELLOWW);
  mt_gotoxy(24, 2);
  std::cout << "Input: ";
  std::cin >> std::dec >> v3;
  mt_setfgcolor(BLUE);
  if (v3 <= 100 && v3 >= 1)
    cur_index = v3 - 1;
}

void key_accumulator() {
  int v;
  mt_setfgcolor(YELLOWW);
  mt_gotoxy(24, 2);
  std::cout << "Input: ";
  std::cin >> std::hex >> v;
  mt_setfgcolor(BLUE);
  v %= 10000;
  accumulator = v;
}

void key_up() {
  if (cur_index > 9)
    cur_index -= 10;
  else if (cur_index >= 0 && cur_index <= 9)
    cur_index += 90;
}

void key_down() {
  if (cur_index < 90)
    cur_index += 10;
  else if (cur_index >= 90 && cur_index <= 99)
    cur_index -= 90;
}

void key_left() {
  if (cur_index > 0)
    cur_index -= 1;
  else if (cur_index == 0)
    cur_index = 99;
}

void key_right() {
  if (cur_index < 99)
    cur_index += 1;
  else if (cur_index == 99)
    cur_index = 0;
}

void main_logic() {
  char *filename = "src_code/obj/memory.bin";
  char *touch_command = "touch src_code/obj/memory.bin";
  sc_regSet(CLOCK_PULSE_IGNORE, true);
  counter = 0;
  signal(SIGALRM, signal_handling_process);
  signal(SIGUSR1, signal_reset);
  KEYS key = None;
  system(touch_command);
  unsigned int tf;
  sc_regGet(CLOCK_PULSE_IGNORE, &tf);
  print_interface();
  while (key != CloseApplication && tf == 1) {
    rk_readkey(key);
    switch (key) {
    case None:
      break;
    case Load:
      sc_memoryLoad(filename);
      print_interface();
      break;
    case Save:
      sc_memorySave(filename);
      print_interface();
      break;
    case Run:
      key_run();
      print_interface();
      break;
    case Step:
      key_step();
      print_interface();
      break;
    case Reset:
      key_reset();
      print_interface();
      break;
    case Accumulator:
      key_accumulator();
      print_interface();
      break;
    case InstructionCounter:
      key_instructionCounter();
      print_interface();
      break;
    case Down:
      key_down();
      break;
    case Up:
      key_up();
      break;
    case Left:
      key_left();
      break;
    case Right:
      key_right();
      break;
    case CloseApplication:
      exit(1);
      break;
    case Enter:
      key_enter();
      break;
    case Compile_asm:
      key_compile_asm();
      break;
    case Compile_basic:
      key_compile_basic();
      break;
    default:
      break;
    }
    if (counter != cur_index) {
      counter = cur_index;
      print_interface();
    }
  }
}
