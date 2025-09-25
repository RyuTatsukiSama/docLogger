#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>
#include "../src/rLogger/rLogger.h"
#include <thread>

static std::string formatedMessage;

void FormatLogTester(std::string _formatedMessage)
{
    formatedMessage = _formatedMessage;
}

TEST(rLoggerTest, FormatLogTest)
{
    std::chrono::system_clock::time_point fixedTime = std::chrono::system_clock::from_time_t(0);
    rLoggerOptions opts = rLoggerOptions::Builder()
                              .setOutputConsole(false)
                              .setOutputFile(false)
                              .setTimeProvider([=]
                                               { return fixedTime; })
                              .build();
    doc::gOpts = &opts;
    rLogger testLogger{};
    testLogger.RegisterLogCallback(FormatLogTester);

    std::string tester = std::format("| [TRACE] [{:%Y-%m-%d %H:%M:%S}] [Main] This is a trace level |", fixedTime);
    testLogger.Log(rLoggerSeverity::Trace, "This is a trace level");
    EXPECT_EQ(formatedMessage, tester);
}

TEST(rLoggerTest, CallerTest)
{
    std::chrono::system_clock::time_point fixedTime = std::chrono::system_clock::from_time_t(0);
    rLoggerOptions opts = rLoggerOptions::Builder()
                              .setOutputConsole(false)
                              .setOutputFile(false)
                              .setTimeProvider([=]
                                               { return fixedTime; })
                              .build();
    doc::gOpts = &opts;
    rLogger logger{};
    logger.RegisterLogCallback(FormatLogTester);

    std::string tester = std::format("| [DEBUG] [{:%Y-%m-%d %H:%M:%S}] [Main] void __cdecl rLoggerTest_CallerTest_Test::TestBody(void) is called |", fixedTime);
    logger.Caller();
    EXPECT_EQ(formatedMessage, tester);
}

TEST(rLoggerTest, SeverityFuncTest)
{
    std::chrono::system_clock::time_point fixedTime = std::chrono::system_clock::from_time_t(0);
    rLoggerOptions opts = rLoggerOptions::Builder()
                              .setOutputConsole(false)
                              .setOutputFile(false)
                              .setTimeProvider([=]
                                               { return fixedTime; })
                              .build();
    doc::gOpts = &opts;
    rLogger logger{};
    logger.RegisterLogCallback(FormatLogTester);

    std::string tester = std::format("| [TRACE] [{:%Y-%m-%d %H:%M:%S}] [Main] Log |", fixedTime);
    logger.Trace("Log");
    EXPECT_EQ(tester, formatedMessage);
    tester = std::format("| [DEBUG] [{:%Y-%m-%d %H:%M:%S}] [Main] Log |", fixedTime);
    logger.Debug("Log");
    EXPECT_EQ(tester, formatedMessage);
    tester = std::format("| [INFO] [{:%Y-%m-%d %H:%M:%S}] [Main] Log |", fixedTime);
    logger.Info("Log");
    EXPECT_EQ(tester, formatedMessage);
    tester = std::format("| [WARNING] [{:%Y-%m-%d %H:%M:%S}] [Main] Log |", fixedTime);
    logger.Warning("Log");
    EXPECT_EQ(tester, formatedMessage);
    tester = std::format("| [ERROR] [{:%Y-%m-%d %H:%M:%S}] [Main] Log |", fixedTime);
    logger.Error("Log");
    EXPECT_EQ(tester, formatedMessage);
    tester = std::format("| [CRITICAL] [{:%Y-%m-%d %H:%M:%S}] [Main] Log |", fixedTime);
    logger.Critical("Log");
    EXPECT_EQ(tester, formatedMessage);
}

TEST(rLoggerTest, WriteFileTest)
{
    std::chrono::system_clock::time_point fixedTime = std::chrono::system_clock::from_time_t(0);
    rLoggerOptions opts = rLoggerOptions::Builder()
                              .setOutputConsole(false)
                              .setFileName("unit_test")
                              .setTimeProvider([=]
                                               { return fixedTime; })
                              .build();
    doc::gOpts = &opts;
    rLogger logger{};

    logger.Trace("Log");
    logger.Debug("Log");
    logger.Info("Log");
    logger.Warning("Log");
    logger.Error("Log");
    logger.Critical("Log");

    std::fstream file("rLogs/unit_test.log", std::ios::in);

    std::string line = "";
    std::getline(file, line);
    EXPECT_EQ(line, "\033[35m| [TRACE] [1970-01-01 00:00:00.0000000] [Main] Log |\033[0m");
    std::getline(file, line);
    EXPECT_EQ(line, "\033[34m| [DEBUG] [1970-01-01 00:00:00.0000000] [Main] Log |\033[0m");
    std::getline(file, line);
    EXPECT_EQ(line, "\033[32m| [INFO] [1970-01-01 00:00:00.0000000] [Main] Log |\033[0m");
    std::getline(file, line);
    EXPECT_EQ(line, "\033[33m| [WARNING] [1970-01-01 00:00:00.0000000] [Main] Log |\033[0m");
    std::getline(file, line);
    EXPECT_EQ(line, "\033[31m| [ERROR] [1970-01-01 00:00:00.0000000] [Main] Log |\033[0m");
    std::getline(file, line);
    EXPECT_EQ(line, "\033[97;41m| [CRITICAL] [1970-01-01 00:00:00.0000000] [Main] Log |\033[0m");
}

void debugThread(const std::string _threadName)
{
    rLogger logger(_threadName);

    logger.Debug("From Debug thread");
}

void errorThread(const std::string _threadName)
{
    rLogger logger(_threadName);

    logger.Error("From Error thread");
}

TEST(rLoggerTest, multithreadTest)
{
    std::chrono::system_clock::time_point fixedTime = std::chrono::system_clock::from_time_t(0);
    rLoggerOptions opts = rLoggerOptions::Builder()
                              .setOutputConsole(false)
                              .setFileName("multithread_test")
                              .setTimeProvider([=]
                                               { return fixedTime; })
                              .build();
    doc::gOpts = &opts;
    rLogger logger{};

    std::thread t1(debugThread, "Debug");

    std::thread t2(errorThread, "Error");

    t1.join();
    t2.join();

    std::ifstream mtTestLog("rLogs/multithread_test.log");

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