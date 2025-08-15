#include <iostream>
#include "../Logger/rLogger.h"

int main()
{
	std::cout << LogSeverity::ERROR.value << std::endl;

	system("pause");

	return 0;
}