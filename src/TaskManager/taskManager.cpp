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
	rLogger log("Main");

	log.Log(rLogSeverity::Log, "This is a log test");

	/*
	std::thread t1(threadFunc, "t1");
	t1.join();

	std::thread t2(threadFunc, "t2");
	t2.join();
	*/

	system("pause");

	return 0;
}