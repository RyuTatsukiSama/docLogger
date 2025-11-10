#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>
#include <Logger.h>
#include <thread>
#include "ThreadIDFormatter.h"
using namespace doc;

static std::string formatedMessage;

void FormatLogTester(std::string _formatedMessage)
{
    formatedMessage = _formatedMessage;
}

TEST(docLoggerTest, FormatLogTest)
{
    // Create a logger with a fixed time provider to have a predictable output
    std::chrono::system_clock::time_point fixedTime = std::chrono::system_clock::from_time_t(0);
    LoggerOptions opts = LoggerOptions::OptionsBuilder()
                             .setOutputConsole(false)
                             .setOutputFile(false)
                             .setTimeProvider([=]
                                              { return fixedTime; })
                             .build();
    Logger testLogger(opts);
    testLogger.RegisterLogCallback(FormatLogTester);

    std::string tester = std::format("| [TRACE] [{:%Y-%m-%d %H:%M:%S}] [{}] This is a trace level |", fixedTime, std::this_thread::get_id());
    testLogger.Log(LoggerSeverity::Trace, "This is a trace level");
    EXPECT_EQ(formatedMessage, tester);
}

TEST(docLoggerTest, CallerTest)
{
    // Create a logger with a fixed time provider to have a predictable output
    std::chrono::system_clock::time_point fixedTime = std::chrono::system_clock::from_time_t(0);
    LoggerOptions opts = LoggerOptions::OptionsBuilder()
                             .setOutputConsole(false)
                             .setOutputFile(false)
                             .setTimeProvider([=]
                                              { return fixedTime; })
                             .build();
    Logger logger(opts);
    logger.RegisterLogCallback(FormatLogTester);

    std::string tester = std::format("| [DEBUG] [{:%Y-%m-%d %H:%M:%S}] [{}] void __thiscall docLoggerTest_CallerTest_Test::TestBody(void) is called |", fixedTime, std::this_thread::get_id());
    logger.Caller();
    EXPECT_EQ(formatedMessage, tester);
}

TEST(docLoggerTest, SeverityFuncTest)
{
    // Create a logger with a fixed time provider to have a predictable output
    std::chrono::system_clock::time_point fixedTime = std::chrono::system_clock::from_time_t(0);
    LoggerOptions opts = LoggerOptions::OptionsBuilder()
                             .setOutputConsole(false)
                             .setOutputFile(false)
                             .setTimeProvider([=]
                                              { return fixedTime; })
                             .build();
    Logger logger(opts);
    logger.RegisterLogCallback(FormatLogTester);

    std::string tester = std::format("| [TRACE] [{:%Y-%m-%d %H:%M:%S}] [{}] Log |", fixedTime, std::this_thread::get_id());
    logger.Trace("Log");
    EXPECT_EQ(tester, formatedMessage);
    tester = std::format("| [DEBUG] [{:%Y-%m-%d %H:%M:%S}] [{}] Log |", fixedTime, std::this_thread::get_id());
    logger.Debug("Log");
    EXPECT_EQ(tester, formatedMessage);
    tester = std::format("| [INFO] [{:%Y-%m-%d %H:%M:%S}] [{}] Log |", fixedTime, std::this_thread::get_id());
    logger.Info("Log");
    EXPECT_EQ(tester, formatedMessage);
    tester = std::format("| [WARNING] [{:%Y-%m-%d %H:%M:%S}] [{}] Log |", fixedTime, std::this_thread::get_id());
    logger.Warning("Log");
    EXPECT_EQ(tester, formatedMessage);
    tester = std::format("| [ERROR] [{:%Y-%m-%d %H:%M:%S}] [{}] Log |", fixedTime, std::this_thread::get_id());
    logger.Error("Log");
    EXPECT_EQ(tester, formatedMessage);
    tester = std::format("| [CRITICAL] [{:%Y-%m-%d %H:%M:%S}] [{}] Log |", fixedTime, std::this_thread::get_id());
    logger.Critical("Log");
    EXPECT_EQ(tester, formatedMessage);
}

TEST(docLoggerTest, WriteFileTest)
{
    // Create a logger with a fixed time provider to have a predictable output
    std::chrono::system_clock::time_point fixedTime = std::chrono::system_clock::from_time_t(0);
    LoggerOptions opts = LoggerOptions::OptionsBuilder()
                             .setOutputConsole(false)
                             .setFileName("unit_test")
                             .setTimeProvider([=]
                                              { return fixedTime; })
                             .build();
                             
    Logger logger(opts);

    logger.Trace("Log");
    logger.Debug("Log");
    logger.Info("Log");
    logger.Warning("Log");
    logger.Error("Log");
    logger.Critical("Log");

    std::fstream file("docLogs/unit_test.log", std::ios::in);

    std::string line = "";
    std::getline(file, line);
    std::string tester = std::format("\033[35m| [TRACE] [1970-01-01 00:00:00.0000000] [{}] Log |\033[0m",std::this_thread::get_id());
    EXPECT_EQ(line, tester);
    std::getline(file, line);
    tester = std::format("\033[34m| [DEBUG] [1970-01-01 00:00:00.0000000] [{}] Log |\033[0m",std::this_thread::get_id());
    EXPECT_EQ(line, tester);
    std::getline(file, line);
    tester = std::format("\033[32m| [INFO] [1970-01-01 00:00:00.0000000] [{}] Log |\033[0m",std::this_thread::get_id());
    EXPECT_EQ(line, tester);
    std::getline(file, line);
    tester = std::format("\033[33m| [WARNING] [1970-01-01 00:00:00.0000000] [{}] Log |\033[0m",std::this_thread::get_id());
    EXPECT_EQ(line, tester);
    std::getline(file, line);
    tester = std::format("\033[31m| [ERROR] [1970-01-01 00:00:00.0000000] [{}] Log |\033[0m",std::this_thread::get_id());
    EXPECT_EQ(line, tester);
    std::getline(file, line);
    tester = std::format("\033[97;41m| [CRITICAL] [1970-01-01 00:00:00.0000000] [{}] Log |\033[0m",std::this_thread::get_id());
    EXPECT_EQ(line, tester);
}

#pragma region Multithreading test

void debugThread(const std::string _threadName)
{
    Logger logger(_threadName);

    logger.Debug("From Debug thread");
}

void errorThread(const std::string _threadName)
{
    Logger logger(_threadName);

    logger.Error("From Error thread");
}

TEST(docLoggerTest, multithreadTest)
{
    // Create a logger with a fixed time provider to have a predictable output
    std::chrono::system_clock::time_point fixedTime = std::chrono::system_clock::from_time_t(0);
    LoggerOptions opts = LoggerOptions::OptionsBuilder()
                             .setOutputConsole(false)
                             .setFileName("multithread_test")
                             .setTimeProvider([=]
                                              { return fixedTime; })
                             .build();
    setGlobalLoggerOptions(opts);
    Logger logger;

    std::thread t1(debugThread, "Debug");

    std::thread t2(errorThread, "Error");

    t1.join();
    t2.join();

    std::ifstream mtTestLog("docLogs/multithread_test.log");

    EXPECT_EQ(mtTestLog.is_open(), true);
    if (mtTestLog.is_open())
    {
        std::vector<std::string> readers;
        std::string reader;

        std::getline(mtTestLog, reader);
        readers.push_back(reader);
        std::getline(mtTestLog, reader);
        readers.push_back(reader);

        EXPECT_THAT(readers, testing::UnorderedElementsAre(
                                 std::format("\x1B[31m| [ERROR] [{:%Y-%m-%d %H:%M:%S}] [Error] From Error thread |\x1B[0m", fixedTime),
                                 std::format("\x1B[34m| [DEBUG] [{:%Y-%m-%d %H:%M:%S}] [Debug] From Debug thread |\x1B[0m", fixedTime)));
    }
}

#pragma endregion