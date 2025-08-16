#include <iostream>
#include "../Logger/rLogger.h"

int main()
{
	std::cout << rLogSeverity::ERROR.value << std::endl;

	system("pause");

	return 0;
}