#include "../src_headers/mySimpleComputer.h"

// 1 - "p" - segmentation fault
// 2 - "0" - error of deleting on null
// 3 - "M" - error out of memory
// 4 - "T" - ignoring tact impulses
// 5 - "E" - invalid command

int memory[100];
unsigned int flags = 0;

int sc_memoryInit() {
  for (int i = 0; i < 100; ++i) {
    memory[i] = 0;
  }
  return 0;
}

int sc_memorySet(int address, int value) {
  if (address >= 0 && address < 100) {
    memory[address] = value;
    return 0;
  } else {
    flags = flags | (1 << (1 - 1));
    return printf("\nError: Segmentation fault\n");
  }
}

int sc_memoryGet(int address, int &value) {
  if (address >= 0 && address < 100) {
    value = memory[address];
  } else {
    flags = flags | (1 << (1 - 1));
    return printf("\nError: Segmentation fault\n");
  }
  return 0;
}

int sc_memorySave(char *filename) {
  FILE *file = nullptr;

  file = fopen(Path, "wb");
  if (file == nullptr) {
    flags = flags | (1 << (1 - 1));
    fclose(file);
    return printf("\nError: Segmentation fault(invalid open file)\n");
  } else {
    fwrite(memory, sizeof(int), 100, file);
    fclose(file);
  }
  return 0;
}

int sc_memoryLoad(char *filename) {
  FILE *file = nullptr;

  file = fopen(Path, "rb");
  if (file == nullptr) {
    flags = flags | (1 << 1);
    fclose(file);
    return printf("\nError: Segmentation fault(invalid open file)\n");
  } else {
    fread(memory, sizeof(int), 100, file);
    fclose(file);
  }

  return 0;
}

int sc_regInit() {
  flags = 0;
  return 0;
}

int sc_regSet(int reg, int value) {
  if ((reg > 5) || (reg < 0)) {
    return -1;
  }
  if (value) {
    flags |= (1 << reg);
  } else {
    flags &= (~(1 << reg));
  }
  return 0;
}

int sc_regGet(int reg, unsigned int *value) {
  if ((reg > 5) || (reg < 0)) {
    return -1;
  }
  *value = ((flags >> reg) & 0x1);
  return 0;
}

vector<string> commands_string_id1 = {"READ", "WRITE", "ADD",   "SUB",  "DIV",
                                      "MUL",  "LOAD",  "STORE", "JUMP", "JNEG",
                                      "JZ",   "HALT",  "MOVA",  "="};

int sc_commandEncode(int str_num, string command, int operand) {
  int command_code;
  vector<string>::iterator it =
      find(commands_string_id1.begin(), commands_string_id1.end(), command);
  if (it != commands_string_id1.end()) {
    int ind = it - commands_string_id1.begin();
    command_code = commands[ind];
  } else {
    sc_regSet(INVALID_COMMAND, 1);
    return -1;
  }
  if (operand <= 0x7F) {
    int value_to_write = (command_code << 7) | operand;
    sc_memorySet(str_num, value_to_write);
    return value_to_write;
  }
  return 0;
}

int sc_commandDecode(string &command, int &operand, int value) {
  int command_vl;
  if (((value >> 14) & 1) == 0) {
    command_vl = value >> 7;
    int ind = find(std::begin(commands), std::end(commands), command_vl) -
              std::begin(commands);
    if (ind < commands_string_id1.size()) {
      command = commands_string_id1[ind];
      operand = value & 0x7F;
      return command_vl;
    }
  }
  return -1;
}
