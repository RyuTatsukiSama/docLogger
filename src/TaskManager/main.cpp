#include "taskManager.h"
using namespace doc;

void anotherFunc(void)
{
    Logger logger(threadName);

    logger.Trace(std::format("Hello from another func in this {} thread", threadName));
}

void debugThread(const std::string _threadName)
{
    Logger logger(_threadName);

    logger.Debug("From debug thread");
    anotherFunc();
}

void errorThread(const std::string _threadName)
{
    Logger logger(_threadName);

    logger.Error("From error thread");
    anotherFunc();
}

int main()
{
    /*std::chrono::system_clock::time_point fixedTime = std::chrono::system_clock::from_time_t(0);
    Logger logger(rLoggerOptionsOld::make({.outputConsole = true,
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
    }

    Logger log(rLoggerOptionsOld::defaults);

    log.Caller();*/

    LoggerOptions opts = LoggerOptions::OptionsBuilder().build();
    gOpts = &opts;

    Logger log("Main");
    log.setSeverityThreshdold(LoggerSeverity::Warning);

    log.Log(LoggerSeverity::Trace, "This is a Trace test");
    log.Log(LoggerSeverity::Debug, "This is a Debug test");
    log.Log(LoggerSeverity::Info, "This is a Info test");
    log.Log(LoggerSeverity::Warning, "This is a Warning test");
    log.Log(LoggerSeverity::Error, "This is a Error test");
    log.Log(LoggerSeverity::Critical, "This is a Critical test");
    std::thread t1(debugThread, "Debug");

    std::thread t2(errorThread, "Error");

    t1.join();
    t2.join();

    system("pause");

    return 0;
}