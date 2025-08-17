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
	std::chrono::time_point now = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());
	std::fstream logFile(std::format("{:%Y-%m-%d_%H-%M-%S}.log", now), std::ios::out);
	log.RegisterOutputStream(&logFile);

	if (!logFile.is_open())
		log.Log(rLogSeverity::Error, "File is not open");

	log.Log(rLogSeverity::Log, "This is a log test");
	log.Log(rLogSeverity::Warning, "This is a Warning test");
	log.Log(rLogSeverity::Error, "This is a Error test");
	log.Log(rLogSeverity::Critical, "This is a Critical test");

	/*
	std::thread t1(threadFunc, "t1");
	t1.join();

	std::thread t2(threadFunc, "t2");
	t2.join();
	*/

	system("pause");

	logFile.close();

	return 0;
}