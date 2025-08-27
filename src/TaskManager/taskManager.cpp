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
	/*std::chrono::system_clock::time_point fixedTime = std::chrono::system_clock::from_time_t(0);
	rLogger logger(rLoggerOptions::make({.outputConsole = true,
										 .fileName = "unit_test",
										 .timeProvider = [=]
										 { return fixedTime; }}));

	logger.Trace("Log");

	std::fstream file("rLogs/unit_test.log", std::ios::in);

	std::string reader = "";
	std::string line = "";
	while (!file.eof())
	{
		file >> reader;
		line += " " + reader;
		if (reader == "|[0m")
		{
			std::cout << line << " and [35m| [TRACE] [1970-01-01 00:00:00.0000000] [Main] Log |[0m" << std::endl;
			std::cout << (line == "[35m| [TRACE] [1970-01-01 00:00:00.0000000] [Main] Log |[0m") << std::endl;
		}
	}*/

	rLogger log(rLoggerOptions::defaults);

	log.Caller();

	log.Log(rLoggerSeverity::Trace, "This is a Trace test");
	log.Log(rLoggerSeverity::Debug, "This is a Debug test");
	log.Log(rLoggerSeverity::Info, "This is a Info test");
	log.Log(rLoggerSeverity::Warning, "This is a Warning test");
	log.Log(rLoggerSeverity::Error, "This is a Error test");
	log.Log(rLoggerSeverity::Critical, "This is a Critical test");

	/*std::thread t1(threadFunc, "t1");
	t1.join();

	std::thread t2(threadFunc, "t2");
	t2.join();
	*/

	system("pause");

	return 0;
}