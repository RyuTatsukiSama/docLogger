#include "taskManager.h"

void threadFunc(const std::string _threadName)
{
	r::threadName = _threadName;
	std::cout << "Hi to " << _threadName << std::endl;
}

void anotherFunc(void)
{
	std::cout << "Another func says hi to " << r::threadName << std::endl;
}

int main()
{
	rLoggerOptions options{
		.outputConsole = true,
		.fileName = "foo"};
	rLogger log(options);

	std::cout << options.fileName;

	log.Log(rLoggerSeverity::Trace, "This is a Trace test");
	log.Log(rLoggerSeverity::Debug, "This is a Debug test");
	log.Log(rLoggerSeverity::Info, "This is a Info test");
	log.Log(rLoggerSeverity::Warning, "This is a Warning test");
	log.Log(rLoggerSeverity::Error, "This is a Error test");
	log.Log(rLoggerSeverity::Critical, "This is a Critical test");

	/*
	std::thread t1(threadFunc, "t1");
	t1.join();

	std::thread t2(threadFunc, "t2");
	t2.join();
	*/

	system("pause");

	return 0;
}