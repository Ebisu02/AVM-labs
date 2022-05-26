#include "../src_headers/basic.h"
#include "../src_headers/assembler.h"
#include "../src_headers/msc.h"

std::vector<int> asm_string_basic_code_counters_id;
std::vector<std::vector<std::string>> asm_code;
std::vector<std::string> vars;
std::vector<std::string> basic_code;
int current_string = 0;
int size = 98;
int asm_string_counter = 0;
const std::string __numbers = "1234567890";

std::string toString(int val) {
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

void sb_input(std::string name, std::vector<std::string> t) {
	// check if this var was defined early
	std::vector<std::string>::iterator it = find(vars.begin(), vars.end(), name);
	if (it != vars.end()) {
		throw std::runtime_error("Error 5: Variable " + name + " was overriden");
	}
	// check if not out of memory(max 100 vars)
	if (vars.size() < 98) {
		std::string code =
			toString(asm_string_counter) + " READ " + toString(vars.size());
		vars.push_back(name);
		++asm_string_counter;
		t.push_back(code);
	}
	else {
		throw std::runtime_error("Error 1: Out of bounds");
	}
	return;
}

void sb_input(std::string name) {
	// check if this var was defined early
	std::vector<std::string>::iterator it = find(vars.begin(), vars.end(), name);
	if (it != vars.end()) {
		throw std::runtime_error("Error 5: Variable " + name + " was overriden");
	}
	// check if not out of memory(max 100 vars)
	if (vars.size() < 98) {
		std::vector<std::string> b;
		std::string code =
			toString(asm_string_counter) + " READ " + toString(vars.size() - 1);
		vars.push_back(name);
		++asm_string_counter;
		b.push_back(code);
		asm_code.push_back(b);
	}
	else {
		throw std::runtime_error("Error 1: Out of bounds");
	}
	return;
}

void sb_print(std::string name) {
	std::vector<std::string>::iterator it = find(vars.begin(), vars.end(), name);
	// check if this var was defined
	if (it != vars.end()) {
		std::vector<std::string> b;
		int memory_cell = it - vars.begin();
		std::string code =
			toString(asm_string_counter) + " WRITE " + toString(memory_cell);
		asm_string_counter++;
		b.push_back(code);
		asm_code.push_back(b);
	}
	else {
		throw std::runtime_error("Error 2: NonImplemented.Variable");
	}
}

void sb_print(std::string name, std::vector<std::string>& t) {
	std::vector<std::string>::iterator it = find(vars.begin(), vars.end(), name);
	// check if this var was defined
	if (it != vars.end()) {
		int memory_cell = it - vars.begin();
		std::string code =
			toString(asm_string_counter) + " WRITE " + toString(memory_cell);
		asm_string_counter++;
		t.push_back(code);
	}
	else {
		throw std::runtime_error("Error 2: NonImplemented.Variable");
	}
}

// REFACTORE!
void sb_goto(int str_num) {
	// NEED TO REFACTORE
	// check if this string num in code exist
	if (str_num < basic_code.size() && str_num > 0) {
		current_string = str_num;
	}
	else {
		throw std::runtime_error("Error 3: NonImplemented.GoToString");
	}
}

// 99 & 100 memory cell for stuff needs

void sb_let(std::string name, std::string left_v, char sign, std::string right_v, std::vector<std::string>& t) {
	if (vars.size() < 98) {
		size_t found = left_v.find_first_not_of("1234567890");
		int left_v_index_of_memory;
		int right_v_index_of_memory;
		// LEFT VALUE
		// check if this is var
		// var
		if (found != std::string::npos) {
			std::vector<std::string>::iterator itl = find(vars.begin(), vars.end(), left_v);
			if (itl != vars.end()) {
				left_v_index_of_memory = itl - vars.begin();
				std::string code = toString(asm_string_counter) + " LOAD " +
					toString(left_v_index_of_memory);
				asm_string_counter++;
				t.push_back(code);
			}
			else {
				throw std::runtime_error("Error 2: NonImplemented.Variable");
			}
		}
		// number
		else {
			int value = std::stoi(left_v);
			value %= 10000;
			std::string code = "98 = " + toString(value);
			t.push_back(code);
			code = toString(asm_string_counter) + " LOAD 98";
			asm_string_counter++;
			t.push_back(code);
		}
		// RIGHT VALUE
		// check if this is var
		// var
		std::string command = "";
		// SIGN
		// check is sign valid and get the command
		switch (sign) {
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
			throw std::runtime_error("Error 2: NonImplemented.SignOperator");
			break;
		}
		found = right_v.find_first_not_of("1234567890");
		if (found != std::string::npos) {
			std::vector<std::string>::iterator itr = find(vars.begin(), vars.end(), right_v);
			if (itr != vars.end()) {
				right_v_index_of_memory = itr - vars.begin();
				std::string code = toString(asm_string_counter) + " " + command + " " +
					toString(right_v_index_of_memory);
				asm_string_counter++;
				t.push_back(code);
			}
			else {
				throw std::runtime_error("Error 2: NonImplemented.Variable");
			}
		}
		// number
		else {
			int value = std::stoi(right_v);
			value %= 10000;
			std::string code = "99 = " + toString(value);
			t.push_back(code);
			code = toString(asm_string_counter) + " " + command + " 99";
			++asm_string_counter;
			t.push_back(code);
		}
		// STORE NEW VAR
		// result in accumulator
		std::vector<std::string>::iterator it = std::find(vars.begin(), vars.end(), name);
		// if var exist it gonna be overwritten
		if (it != vars.end()) {
			int mem_c = it - vars.begin();
			std::string code = toString(asm_string_counter) + " STORE " + toString(mem_c);
			asm_string_counter++;
			t.push_back(code);
		}
		// if not then it gonna be defined
		else {
			std::string code =
				toString(asm_string_counter) + " STORE " + toString(vars.size() - 1);
			asm_string_counter++;
			t.push_back(code);
		}
	}
	else {
		throw std::runtime_error("Error 1: Out of bounds");
	}
}

void sb_let(std::string name, std::string left_v, char sign, std::string right_v) {
	if (vars.size() < 98) {
		size_t found = left_v.find_first_not_of("1234567890");
		std::vector<std::string> b;
		int left_v_index_of_memory;
		int right_v_index_of_memory;
		// LEFT VALUE
		// check if this is var
		// var
		if (found != std::string::npos) {
			std::vector<std::string>::iterator itl = find(vars.begin(), vars.end(), left_v);
			if (itl != vars.end()) {
				left_v_index_of_memory = itl - vars.begin();
				std::string code = toString(asm_string_counter) + " LOAD " +
					toString(left_v_index_of_memory);
				asm_string_counter++;
				b.push_back(code);
			}
			else {
				throw std::runtime_error("Error 2: NonImplemented.Variable");
			}
		}
		// number
		else {
			int value = std::stoi(left_v);
			value %= 10000;
			std::string code = "98 = " + toString(value);
			b.push_back(code);
			code = toString(asm_string_counter) + " LOAD 98";
			asm_string_counter++;
			b.push_back(code);
		}
		// RIGHT VALUE
		// check if this is var
		// var
		std::string command = "";
		// SIGN
		// check is sign valid and get the command
		switch (sign) {
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
			throw std::runtime_error("Error 2: NonImplemented.SignOperator");
			break;
		}
		found = right_v.find_first_not_of("1234567890");
		if (found != std::string::npos) {
			std::vector<std::string>::iterator itr = find(vars.begin(), vars.end(), right_v);
			if (itr != vars.end()) {
				right_v_index_of_memory = itr - vars.begin();
				std::string code = toString(asm_string_counter) + " " + command + " " +
					toString(right_v_index_of_memory);
				asm_string_counter++;
				b.push_back(code);
			}
			else {
				throw std::runtime_error("Error 2: NonImplemented.Variable");
			}
		}
		// number
		else {
			int value = std::stoi(right_v);
			value %= 10000;
			std::string code = "99 = " + toString(value);
			b.push_back(code);
			code = toString(asm_string_counter) + " " + command + " 99";
			++asm_string_counter;
			b.push_back(code);
		}
		// STORE NEW VAR
		// result in accumulator
		std::vector<std::string>::iterator it = std::find(vars.begin(), vars.end(), name);
		// if var exist it gonna be overwritten
		if (it != vars.end()) {
			int mem_c = it - vars.begin();
			std::string code = toString(asm_string_counter) + " STORE " + toString(mem_c);
			asm_string_counter++;
			b.push_back(code);
		}
		// if not then it gonna be defined
		else {
			std::string code =
				toString(asm_string_counter) + " STORE " + toString(vars.size() - 1);
			asm_string_counter++;
			b.push_back(code);
		}
		asm_code.push_back(b);
	}
	else {
		throw std::runtime_error("Error 1: Out of bounds");
	}
}

void sb_end() {
	std::vector<std::string> b;
	std::string code = toString(asm_string_counter) + " HALT 00";
	asm_string_counter++;
	b.push_back(code);
	asm_code.push_back(b);
}

void sb_end(std::vector<std::string>& t) {
	std::string code = toString(asm_string_counter) + " HALT 00";
	asm_string_counter++;
	t.push_back(code);
}

bool is_only_numbers_in_string(const std::string __str)
{
	size_t found = __str.find_first_not_of("1234567890");
	if (found != std::string::npos)
		return false;
	else
		return true;
}

// 20 LET A = B + 20
void sb_parse_let(std::string cmd, int& str_num, std::string& name, std::string& left_v, char& sign, std::string& right_v)
{
	std::string str_num_string = "";
	name = "", left_v = "", right_v = "";
	std::string::iterator it = cmd.begin();
	int counter = 0;
	while (it != cmd.end())
	{
		if (*it == ' ' && counter > 6)
		{
			break;
		}
		else if (*it == ' ')
		{
			++it;
			++counter;
		}
		if (counter == 0)
		{
			str_num_string += *it;
		}
		else if (counter == 2)
		{
			name += *it;
		}
		else if (counter == 4)
		{
			left_v += *it;
		}
		else if (counter == 5)
		{
			sign = *it;
		}
		else if (counter == 6)
		{
			right_v += *it;
		}
		++it;
	}
	if (is_only_numbers_in_string(str_num_string) && !(str_num_string.empty() &&
		name.empty() && left_v.empty() && sign != '0' && right_v.empty()))
	{
		str_num = std::stoi(str_num_string);
	}
	else
	{
		throw std::runtime_error("syntax error");
	}
}

// 20 GOTO 10
void sb_parse_goto(std::string cmd, int& str_num, int& operand)
{
	std::string str_num_string = "", cmd_string = "", operand_string = "";
	std::string::iterator it = cmd.begin();
	int counter = 0;
	while (it != cmd.end())
	{
		if (*it == ' ' && counter > 2)
		{
			break;
		}
		else if (*it == ' ')
		{
			++it;
			++counter;
		}
		if (counter == 0)
		{
			str_num_string += *it;
			++it;
		}
		else if (counter == 1)
		{
			cmd_string += *it;
			++it;
		}
		else if (counter == 2)
		{
			operand_string += *it;
			++it;
		}
	}
	if (is_only_numbers_in_string(str_num_string) && is_only_numbers_in_string(operand_string)
		&& !str_num_string.empty() && !operand_string.empty())
	{
		str_num = std::stoi(str_num_string);
		operand = std::stoi(operand_string);
	}
	else
	{
		throw std::runtime_error("syntax error");
	}
	return;
}

// 10 INPUT A
void sb_parse_input_or_print(std::string cmd, int& str_num, std::string& name)
{
	name = "";
	std::string str_num_string = "";
	std::string::iterator it = cmd.begin();
	int counter = 0;
	while (it != cmd.end())
	{
		if (*it == ' ' && counter > 2)
		{
			break;
		}
		else if (*it == ' ')
		{
			++it;
			++counter;
		}
		if (counter == 0)
		{
			str_num_string += *it;
		}
		else if (counter == 2)
		{
			name += *it;
		}
		++it;
	}
	if (!name.empty() && !str_num_string.empty() && is_only_numbers_in_string(str_num_string))
	{
		str_num = std::stoi(str_num_string);
	}
	else
	{
		throw std::runtime_error("syntax error");
	}
}

// 10 IF A > 20 PRINT A
void sb_parse_if(std::string cmd, int& str_num, std::string& right_value, std::string& left_value, std::string& cond, std::string& operand, int& operand_length)
{
	std::string::iterator it = cmd.begin();
	std::string str_num_string = "";
	right_value = "", cond = "", left_value = "", operand = "";
	int counter = 0;
	while (it != cmd.end())
	{
		if (*it == ' ' && counter < 5)
		{
			++counter;
			++it;
		}
		if (counter == 0)
		{
			str_num_string += *it;
		}
		else if (counter == 2)
		{
			left_value += *it;
		}
		else if (counter == 3)
		{
			cond += *it;
		}
		else if (counter == 4)
		{
			right_value += *it;
		}
		else if (counter >= 5)
		{
			operand += *it;
		}
		++it;
	}
	if (!right_value.empty() && !cond.empty() && !left_value.empty() &&
		!str_num_string.empty() && !operand.empty() && is_only_numbers_in_string(str_num_string))
	{
		str_num = std::stoi(str_num_string);
		std::string temp = str_num_string + " ";
		operand = temp + operand;
		operand_length = 0;
		if (operand.find("GOTO") != std::string::npos
			|| operand.find("INPUT") != std::string::npos
			|| operand.find("PRINT") != std::string::npos
			|| operand.find("END") != std::string::npos)
			operand_length = 1;
		else if (operand.find("LET") != std::string::npos)
			operand_length = 3;
		else
			throw std::runtime_error("Invalid 'if' operand command");
		//std::cout << str_num << left_value << cond << right_value << operand << operand_length;
	}
	else
	{
		throw std::runtime_error("syntax error");
	}
}

int sb_parse_string_cmd(std::string cmd, std::vector<std::string> cmd_asm_code)
{
	try
	{
		int str_num;
		int operand;
		int cmd_length = asm_string_counter;
		if (cmd.find("GOTO") != std::string::npos)
		{
			sb_parse_goto(cmd, str_num, operand);
			//std::cout << str_num << " " << operand;
			sb_goto(operand);
		}
		else if (cmd.find("REM") != std::string::npos)
		{
			// pass
		}
		else if (cmd.find("LET") != std::string::npos)
		{
			std::string name = "", left_v = "", right_v = "";
			char sign = '0';
			sb_parse_let(cmd, str_num, name, left_v, sign, right_v);
			//std::cout << str_num << name << left_v << sign << right_v;
			sb_let(name, left_v, sign, right_v, cmd_asm_code);
		}
		else if (cmd.find("END") != std::string::npos)
		{
			sb_end();
		}
		else if (cmd.find("INPUT") != std::string::npos)
		{
			std::string name = "";
			sb_parse_input_or_print(cmd, str_num, name);
			//std::cout << str_num << name;
			sb_input(name, cmd_asm_code);
		}
		else if (cmd.find("PRINT") != std::string::npos)
		{
			std::string name = "";
			sb_parse_input_or_print(cmd, str_num, name);
			//std::cout << str_num << name;
			sb_print(name, cmd_asm_code);
		}
		else
		{
			throw std::runtime_error("invalid command");
		}
		asm_string_basic_code_counters_id.push_back(str_num);
		cmd_length = asm_string_counter - cmd_length;
		return cmd_length;
	}
	catch (std::runtime_error e)
	{
		std::cout << "\n" << e.what() << "\n";
		return -1;
	}
}

void sb_if(std::string cmd, std::string left_value, std::string right_value, std::string cond, int cmd_len_asm)
{
	std::vector<std::string> b;
	int left_value_mem_cell;
	int right_value_mem_cell;
	// Lets get the vars or consts values from both sides of condition
	// ----------
	// LEFT VALUE
	std::size_t found = left_value.find_first_not_of(__numbers);
	// var
	if (found != std::string::npos)
	{
		using namespace std;
		vector<string>::iterator itlv = find(vars.begin(), vars.end(), left_value);
		if (itlv != vars.end())
		{
			left_value_mem_cell = itlv - vars.begin();
		}
		else
		{
			std::cout << "Error 2: NonImplemented.Variable";
		}
	}
	// number
	else
	{
		left_value_mem_cell = 98;
		std::string code = "98 = " + atoi(left_value.c_str());
		b.push_back(code);
	}
	//--------------
	// RIGHT VALUE
	//--------------
	// var
	found = right_value.find_first_not_of(__numbers);
	if (found != std::string::npos)
	{
		using namespace std;
		vector<string>::iterator itrv = find(vars.begin(), vars.end(), right_value);
		if (itrv != vars.end())
		{
			right_value_mem_cell = itrv - vars.begin();
		}
		else
		{
			std::cout << "Error 2: NonImplemented.Variable";
		}
	}
	// number
	else
	{
		right_value_mem_cell = 99;
		std::string code = "99 = " + atoi(right_value.c_str());
		b.push_back(code);
	}
	// Lets parse the condition, using jneg & jz
	// >, <, !=, ==
	if (cond == ">")
	{
		// a - left value
		// b - right value
		// c - str num
		// s - goto str where end if [cmd] 
		// ===================================
		// | c        LOAD      a            |
		// | c + 1    SUB       b            |
		// | c + 2    JNEG      s            |
		// ===================================
		b.push_back(toString(asm_string_counter) + " LOAD " + toString(left_value_mem_cell));
		++asm_string_counter;
		b.push_back(toString(asm_string_counter) + " SUB " + toString(right_value_mem_cell));
		++asm_string_counter;
		b.push_back(toString(asm_string_counter) + " JNEG " + toString(asm_string_counter + cmd_len_asm));
		++asm_string_counter;
		sb_parse_string_cmd(cmd, b);
	}
	else if (cond == "<")
	{
		// a - left value
		// b - right value
		// c - str num
		// s - goto str where end if [cmd] 
		// ===================================
		// | c        LOAD      b            |
		// | c + 1    SUB       a            |
		// | c + 2    JNEG      s            |
		// ===================================
		b.push_back(toString(asm_string_counter) + " LOAD " + toString(right_value_mem_cell));
		++asm_string_counter;
		b.push_back(toString(asm_string_counter) + " SUB " + toString(left_value_mem_cell));
		++asm_string_counter;
		b.push_back(toString(asm_string_counter) + " JNEG " + toString(asm_string_counter + cmd_len_asm));
		++asm_string_counter;
		sb_parse_string_cmd(cmd, b);
	}
	else if (cond == "!=")
	{
		// a - left value
		// b - right value
		// c - str num
		// s - goto str where end if [cmd] 
		// ===================================
		// | c        LOAD      a            |
		// | c + 1    SUB       b            |
		// | c + 2    JZ        s            |
		// ===================================
		b.push_back(toString(asm_string_counter) + " LOAD " + toString(right_value_mem_cell));
		++asm_string_counter;
		b.push_back(toString(asm_string_counter) + " SUB " + toString(left_value_mem_cell));
		++asm_string_counter;
		b.push_back(toString(asm_string_counter) + " JZ " + toString(asm_string_counter + cmd_len_asm));
		++asm_string_counter;
		sb_parse_string_cmd(cmd, b);
	}
	else if (cond == "==")
	{
		// a - left value
		// b - right value
		// c - str num
		// s - goto str where end if [cmd] 
		// =================================
		// | c		 LOAD		a		   |
		// | c + 1	 SUB		b		   |
		// | c + 2	 JZ			s - 1	   |
		// | c + 3	 JUMP		s		   |
		// | ...	 ....		...		   |
		// | s - 1   JUMP		c + 4      |
		// =================================
		b.push_back(toString(asm_string_counter) + " LOAD " + toString(left_value_mem_cell));
		++asm_string_counter;
		b.push_back(toString(asm_string_counter) + " SUB " + toString(right_value_mem_cell));
		++asm_string_counter;
		b.push_back(toString(asm_string_counter) + " JZ " + toString(asm_string_counter + cmd_len_asm + 1));
		++asm_string_counter;
		b.push_back(toString(asm_string_counter) + " JUMP " + toString(asm_string_counter + cmd_len_asm + 1));
		++asm_string_counter;
		int tmp = asm_string_counter;
		sb_parse_string_cmd(cmd, b);
		b.push_back(toString(asm_string_counter) + " JUMP " + toString(tmp));
		++asm_string_counter;
	}
	else
	{
		throw std::runtime_error("ERROR 4: NONIMPLEMENTED.COMPARISONSIGNATURE");
	}
	//--------------
	// Lets parse the command
	// std::string cmd 
	// Idea - parse the command and get the counter where this command ends in assembler
	asm_code.push_back(b);
}

int sb_parse_string_cmd(std::string cmd)
{
	try
	{
		int str_num;
		int operand;
		int cmd_length = asm_string_counter;
		if (cmd.find("GOTO") != std::string::npos)
		{
			sb_parse_goto(cmd, str_num, operand);
			//std::cout << str_num << " " << operand;
			sb_goto(operand);
		}
		else if (cmd.find("IF") != std::string::npos)
		{
			std::string rv, lv, cnd, opr;
			int opr_len;
			sb_parse_if(cmd, str_num, rv, lv, cnd, opr, opr_len);
			sb_if(opr, lv, rv, cnd, opr_len);
		}
		else if (cmd.find("REM") != std::string::npos)
		{
			// pass
		}
		else if (cmd.find("LET") != std::string::npos)
		{
			std::string name = "", left_v = "", right_v = "";
			char sign = '0';
			sb_parse_let(cmd, str_num, name, left_v, sign, right_v);
			//std::cout << str_num << name << left_v << sign << right_v;
			sb_let(name, left_v, sign, right_v);
		}
		else if (cmd.find("END") != std::string::npos)
		{
			sb_end();
		}
		else if (cmd.find("INPUT") != std::string::npos)
		{
			std::string name = "";
			sb_parse_input_or_print(cmd, str_num, name);
			//std::cout << str_num << me;
			sb_input(name);
		}
		else if (cmd.find("PRINT") != std::string::npos)
		{
			std::string name = "";
			sb_parse_input_or_print(cmd, str_num, name);
			//std::cout << str_num << name;
			sb_print(name);
		}
		else
		{
			throw std::runtime_error("invalid command");
		}
		asm_string_basic_code_counters_id.push_back(str_num);
		cmd_length = asm_string_counter - cmd_length;
		return cmd_length;
	}
	catch (std::runtime_error e)
	{
		std::cout << "\n" << e.what() << "\n";
		return -1;
	}
}

void sb_manager(std::string path_to_file, std::string path_to_asm_file, std::string path_to_obj_file)
{
	std::ifstream fin(path_to_file);
	if (!fin.is_open())
	{
		return;
	}
	std::string tmp = "";
	while (getline(fin, tmp))
	{
		sb_parse_string_cmd(tmp);
	}
	std::ofstream fout(path_to_asm_file);
	if (!fout.is_open())
	{
		return;
	}
	for (int i = 0; i < asm_code.size(); ++i)
	{
		for (int j = 0; j < asm_code[i].size(); ++j)
		{
			fout << asm_code[i][j] << "\n";
		}
	}
	// delegate this asm file to asm_lib function
	fout.close();
	fin.close();
	sas_manager(path_to_asm_file, path_to_obj_file);
}
