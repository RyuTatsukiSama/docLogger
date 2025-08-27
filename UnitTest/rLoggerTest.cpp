#include <gtest/gtest.h>
#include "../src/rLogger/rLogger.h"

static std::string formatedMessage;

void FormatLogTester(std::string _formatedMessage)
{
    formatedMessage = _formatedMessage;
}

TEST(rLoggerTest, FormatLogTest)
{
    std::chrono::system_clock::time_point fixedTime = std::chrono::system_clock::from_time_t(0);
    rLogger testLogger(rLoggerOptions::make({.outputConsole = false,
                                             .outputFile = false,
                                             .timeProvider = [=]
                                             { return fixedTime; }}));
    testLogger.RegisterLogCallback(FormatLogTester);

    std::string tester = std::format("| [TRACE] [{:%Y-%m-%d %H:%M:%S}] [Main] This is a trace level |", fixedTime);
    testLogger.Log(rLoggerSeverity::Trace, "This is a trace level");
    EXPECT_EQ(formatedMessage, tester);
}

TEST(rLoggerTest, CallerTest)
{
    rLogger logger{rLoggerOptions::make({.outputConsole = false,
                                         .outputFile = false})};

    logger.Caller();
}

TEST(rLoggerTest, SeverityFuncTest)
{
    std::chrono::system_clock::time_point fixedTime = std::chrono::system_clock::from_time_t(0);
    rLogger logger{rLoggerOptions::make({.outputConsole = false,
                                         .outputFile = false,
                                         .timeProvider = [=]
                                         { return fixedTime; }})};
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

TEST(rLoggertest, WriteFileTest)
{
    std::chrono::system_clock::time_point fixedTime = std::chrono::system_clock::from_time_t(0);
    rLogger logger(rLoggerOptions::make({.outputConsole = false,
                                         .fileName = "unit_test",
                                         .timeProvider = [=]
                                         { return fixedTime; }}));

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