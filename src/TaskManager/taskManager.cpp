#include "taskManager.h"

void threadFunc(const std::string _threadName)
{
	threadName = _threadName;
	std::cout << "Hi to " << _threadName << std::endl;
}

void anotherFunc(void)
{
	std::cout << "Another func says hi to " << threadName << std::endl;
}

int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// you can loop k higher to see more color choices
	for (int k = 1; k < 255; k++)
	{
		// pick the colorattribute k you want
		SetConsoleTextAttribute(hConsole, k);
		std::cout << k << " I want to be nice today!" << std::endl;
	}

	/*
	std::thread t1(threadFunc, "t1");
	t1.join();

	std::thread t2(threadFunc, "t2");
	t2.join();
	*/

	system("pause");

	return 0;
}