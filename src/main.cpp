#include "mySimpleComputer.h"

int main()
{
	sc_memoryInit();
	sc_memorySet(0, 1);
	int value = sc_memoryGet(0, value);
	cout << value;
	cout << "\n";
	sc_memorySave(Path);
	sc_memorySet(0, 2);
	sc_memoryLoad(Path);
	sc_regInit();
	sc_regSet(1, 1);
	unsigned int flag_value = sc_regGet(1, &flag_value);
	return 0;
}
