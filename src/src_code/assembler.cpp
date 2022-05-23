#include "../src_headers/assembler.h"
#include "../src_headers/msc.h"

int sas_from_string_to_int(string operand)
{
	return stoi(operand);
}

void sas_remove_extra_spaces_from_asm_string(string& str)
{
	for (string::iterator it = str.begin(); it != str.end(); ++it)
	{
		string::iterator begin = it;
		while (it != str.end() && ::isspace(*it))
			++it;
		if (it - begin > 1)
		{
			it = str.erase(begin + 1, it) - 1;
		}
	}
}

void sas_read_asm_string(string s, int& string_num, string& command, string& operand)
{
	command = "";
	operand = "";
	while (true)
	{
		// [command]_[operand]_;comment
		bool fcommand = true;
		bool foperand = false;
		bool end = false;
		int start;
		string num = "";
		for (start = 0; start < s.size(); ++start)
		{
			if (s[start] == ' ')
			{
				break;
			}
			else
			{
				num += s[start];
			}
		}
		string_num = sas_from_string_to_int(num);
		start++;
		for (int i = start; i < s.size(); ++i)
		{
			if (s[i] == ';')
			{
				end = true;
				break;
			}
			if (i == 0 && s[0] == ' ')
				throw runtime_error("Error 1: Syntax error");
			if (s[i] == ' ' && fcommand)
			{
				fcommand = false;
				foperand = true;
				continue;
			}
			if (s[i] == ' ' && foperand)
			{
				foperand = false;
				continue;
			}
			if (!fcommand && !foperand &&
				(s[i] != ';' && s[i] != ' '))
				throw runtime_error("Error 1: Syntax error");
			if (fcommand)
				command += s[i];
			if (foperand)
				operand += s[i];
			if (i == s.size() - 1)
				end = true;
		}
		if (end)
			break;
	}
}

int sas_equals(int address, int value)
{
	if (address < 0 || address > 99)
	{
		return 1;
	}
	value %= 10000;
	sc_memorySet(address, value);
	return 0;
}

int sas_read(int address)
{
	if (address < 0 || address > 99)
	{
		// Segmentation fault
		return 1;
	}
	int value;
	//std::cout << "\nPlease enter a value for memory cell #" << address << " - ";
	std::cout << "\nInput: ";
	std::cin >> value;
	value %= 10000;
	sc_memorySet(address, value);
	value = sc_memoryGet(address, value);
	//std::cout << value;
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
	//std::cout << "\nValue in memory cell #" << address << " - " << value;
	std::cout << "\nOutput: " << value << "\n";
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
	if (v1 != 0)
	{
		res = accumulator / v1;
		res %= 10000;
		set_accumulator(res);
	}
	else
	{
		throw runtime_error("Critical Error: Division by zero");
	}
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
	throw runtime_error("Error 0: All ok"); // signal to end assembler code
}

int sas_mova(int address, int accumulator)
{
	int v1;
	sc_memoryGet(address, v1);
	sc_memorySet(accumulator, v1);
	sc_memorySet(address, 0);
	return 0; // is ok?
}

bool sas_is_operand_correct(string operand)
{
	size_t found = operand.find_first_not_of("1234567890");
	if (found != string::npos)
		throw runtime_error("Error 4: Incorrect operand");
	else
		return true;
	return false;
}

// ../scripts/asm/[filename].asm
void sas_manager(string path_to_file)
{
	try
	{
		ifstream file1(path_to_file);
		string s;
		int counter = 0;
/*		mt_gotoxy(30 + counter,2);
		std::cout << file1.is_open();*/
		while (getline(file1, s) && ++counter)
		{
			mt_gotoxy(30 + counter,2);
			if (s.empty())
			{
				// some test code for debuging
				continue;
			}
			sas_remove_extra_spaces_from_asm_string(s);
			int string_num;
			string command;
			string operand;
			sas_read_asm_string(s, string_num, command, operand);
			sas_is_operand_correct(operand);
			int opr = sas_from_string_to_int(operand);
			if (command == "READ")
			{ 
				sas_read(opr);
				//break;
			}
			else if (command == "WRITE")
			{
				sas_write(opr);
				//break;
			}
			else if (command == "LOAD")
			{
				sas_load(opr);
				//break;
			}
			else if (command == "STORE")
			{
				sas_store(get_accumulator(), opr);
				//break;
			}
			else if (command == "ADD")
			{
				sas_add(get_accumulator(), opr);
				//break;
			}
			else if (command == "SUB")
			{
				sas_sub(get_accumulator(), opr);
				//break;
			}
			else if (command == "DIV")
			{
				sas_div(get_accumulator(), opr);
				//break;
			}
			else if (command == "MUL")
			{
				sas_mul(get_accumulator(), opr);
				//break;
			}
			else if (command == "JUMP")
			{
				sas_jump(opr);
				//break;
			}
			else if (command == "JNEG")
			{
				sas_jneg(get_accumulator(), opr);
				//break;
			}
			else if (command == "JZ")
			{
				sas_jz(get_accumulator(), opr);
				//break;
			}
			else if (command == "MOVA")
			{
				sas_mova(opr, get_accumulator());
				//break;
			}
			else if (command == "=")
			{
				sas_equals(string_num, opr);
			}
			else if (command == "HALT")
			{
				sas_halt();
				//break;
			}
			else
			{
				throw runtime_error("Error 2: Unknown command"); 
				break;
			}
		}
		file1.close();
	}
	catch(runtime_error e)
	{
		cout << "\n" << e.what() << "\n";
		return;
	}
}