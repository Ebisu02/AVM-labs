#include "../src_headers/basic.h"

vector<string> asm_code;
vector<string> vars;
vector<string> basic_code;
int current_string = 0;
int size = 98;
int asm_string_counter = 0;

string toString(int val)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

void sb_input(string name)
{
	//check if this var was defined early
	vector<string>::iterator it = find(vars.begin(), vars.end(), name);
	if (it != vars.end())
	{
		throw runtime_error("Error 5: Variable " + name + " was overriden");
	}
	//check if not out of memory(max 100 vars)
	if (vars.size() < 98)
	{
		string code = toString(asm_string_counter) + " READ " + toString(vars.size() - 1);
		vars.push_back(name);
		++asm_string_counter;
		asm_code.push_back(code);
	}
	else
	{
		throw runtime_error("Error 1: Out of bounds");
	}
	return;
}

void sb_print(string name)
{
	vector<string>::iterator it = find(vars.begin(), vars.end(), name);
	//check if this var was defined
	if (it != vars.end())
	{
		int memory_cell = it - vars.begin();
		string code = toString(asm_string_counter) + " WRITE " + toString(memory_cell);
		asm_string_counter++;
		asm_code.push_back(code);
	}
	else
	{
		throw runtime_error("Error 2: NonImplemented.Variable");
	}
}

void sb_goto(int str_num)
{
	// check if this string num in code exist
	if (str_num < basic_code.size() && str_num > 0)
	{
		current_string = str_num;
	}
	else
	{
		throw runtime_error("Error 3: NonImplemented.GoToString");
	}
}

void sb_if(string left_value, string cond, string right_value, string command)
{
	// >, <, >=, <=, !=, ==
	if (cond == ">")
	{
		// A > 20 LET A = 20 + 1
		

	}
	else if (cond == "<")
	{

	}
	else if (cond == ">=")
	{

	}
	else if (cond == "<=")
	{

	}
	else if (cond == "!=")
	{

	}
	else if (cond == "==")
	{

	}
	else
	{
		throw runtime_error("Error 4: NonImplemented.ComparisonSign");
	}
}

// 99 & 100 memory cell for stuff needs

void sb_let(string name, string left_v, char sign, string right_v)
{
	if (vars.size() < 98)
	{
		size_t found = left_v.find_first_not_of("1234567890");
		int left_v_index_of_memory;
		int right_v_index_of_memory;
		// LEFT VALUE 
		// check if this is var
		// var
		if (found != string::npos)
		{
			vector<string>::iterator itl = find(vars.begin(), vars.end(), left_v);
			if (itl != vars.end())
			{
				left_v_index_of_memory = itl - vars.begin();
				string code = toString(asm_string_counter) + " LOAD " + toString(left_v_index_of_memory);
				asm_string_counter++;
				asm_code.push_back(code);
			}
			else
			{
				throw runtime_error("Error 2: NonImplemented.Variable");
			}
		}
		// number
		else
		{
			int value = sas_from_string_to_int(left_v);
			value %= 10000;
			string code = "98 = " + toString(value);
			asm_code.push_back(code);
			code = toString(asm_string_counter) + " LOAD 98";
			asm_string_counter++;
			asm_code.push_back(code);
		}
		// RIGHT VALUE
		// check if this is var
		// var
		string command = "";
		// SIGN
		// check is sign valid and get the command
		switch(sign)
		{
			case '+':
				command = "ADD";
				break;
			case '-':
				command = "SUB";
				break;
			case '/':
				command = "DIV";
				break;
			case '*':
				command = "MUL";
				break;
			default:
				throw runtime_error("Error 2: NonImplemented.SignOperator");
				break;
		}
		found = right_v.find_first_not_of("1234567890");
		if (found != string::npos)
		{
			vector<string>::iterator itr = find(vars.begin(), vars.end(), right_v);
			if (itr != vars.end())
			{
				right_v_index_of_memory = itr - vars.begin();
				string code = toString(asm_string_counter) + " " + command + " " + toString(right_v_index_of_memory);
				asm_string_counter++;
				asm_code.push_back(code);
			}
			else
			{
				throw runtime_error("Error 2: NonImplemented.Variable");
			}
		}
		// number
		else
		{
			int value = sas_from_string_to_int(right_v);
			value %= 10000;
			string code = "99 = " + toString(value);
			asm_code.push_back(code);
			code = toString(asm_string_counter) + " " + command + " 99";
			++asm_string_counter;
			asm_code.push_back(code);
		}
		// STORE NEW VAR
		// result in accumulator 
		vector<string>::iterator it = find(vars.begin(), vars.end(), name);
		// if var exist it gonna be overwritten
		if (it != vars.end())
		{
			int mem_c = it - vars.begin();
			string code = toString(asm_string_counter) + " LOAD " + toString(mem_c);
			asm_string_counter++;
			asm_code.push_back(code);
		}
		// if not then it gonna be defined 
		else
		{
			string code = toString(asm_string_counter) + " LOAD " + toString(vars.size() - 1);
			asm_string_counter++;
			asm_code.push_back(code); 
		}
	}
	else
	{
		throw runtime_error("Error 1: Out of bounds");
	}
}

void sb_end()
{
	string code = toString(asm_string_counter) + " HALT 00";
	asm_string_counter++;
	asm_code.push_back(code); 
}