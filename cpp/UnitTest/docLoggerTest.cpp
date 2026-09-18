#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>
#include <doc/Logger.h>
#include <thread>
#include <doc/ThreadIDFormatter.h>

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

    std::string tester = std::format("[\x1B[45mTRACE\x1B[0m] [\x1B[30;47m{}\x1B[0m] [{:%Y-%m-%d %H:%M:%S}] This is a trace level" , std::this_thread::get_id(), fixedTime); // NOSONAR
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
#if WIN32
    std::string tester = std::format("[\x1B[44mDEBUG\x1B[0m] [\x1B[30;47m{}\x1B[0m] [{:%Y-%m-%d %H:%M:%S}] void __cdecl docLoggerTest_CallerTest_Test::TestBody(void) is called", std::this_thread::get_id(), fixedTime); // NOSONAR
#else
    std::string tester = std::format("[\x1B[44mDEBUG\x1B[0m] [\x1B[30;47m{}\x1B[0m] [{:%Y-%m-%d %H:%M:%S}] virtual void docLoggerTest_CallerTest_Test::TestBody() is called", std::this_thread::get_id(), fixedTime); // NOSONAR
#endif
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

    std::string tester = std::format("[\x1B[45mTRACE\x1B[0m] [\x1B[30;47m{}\x1B[0m] [{:%Y-%m-%d %H:%M:%S}] Log", std::this_thread::get_id(), fixedTime); // NOSONAR
    logger.Trace("Log");
    EXPECT_EQ(tester, formatedMessage);
    tester = std::format("[\x1B[44mDEBUG\x1B[0m] [\x1B[30;47m{}\x1B[0m] [{:%Y-%m-%d %H:%M:%S}] Log", std::this_thread::get_id(), fixedTime); // NOSONAR
    logger.Debug("Log");
    EXPECT_EQ(tester, formatedMessage);
    tester = std::format("[\x1B[42mINFO\x1B[0m] [\x1B[30;47m{}\x1B[0m] [{:%Y-%m-%d %H:%M:%S}] Log", std::this_thread::get_id(), fixedTime); // NOSONAR
    logger.Info("Log");
    EXPECT_EQ(tester, formatedMessage);
    tester = std::format("[\x1B[43mWARNING\x1B[0m] [\x1B[30;47m{}\x1B[0m] [{:%Y-%m-%d %H:%M:%S}] Log", std::this_thread::get_id(), fixedTime); // NOSONAR
    logger.Warning("Log");
    EXPECT_EQ(tester, formatedMessage);
    tester = std::format("[\x1B[41mERROR\x1B[0m] [\x1B[30;47m{}\x1B[0m] [{:%Y-%m-%d %H:%M:%S}] Log", std::this_thread::get_id(), fixedTime); // NOSONAR
    logger.Error("Log");
    EXPECT_EQ(tester, formatedMessage);
    tester = std::format("[\x1B[31;47mCRITICAL\x1B[0m] [\x1B[30;47m{}\x1B[0m] [{:%Y-%m-%d %H:%M:%S}] Log", std::this_thread::get_id(), fixedTime); // NOSONAR
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
    std::string tester = std::format("[\x1B[45mTRACE\x1B[0m] [\x1B[30;47m{}\x1B[0m] [{:%Y-%m-%d %H:%M:%S}] Log", std::this_thread::get_id(), fixedTime); // NOSONAR
    EXPECT_EQ(line, tester);
    std::getline(file, line);
    tester = std::format("[\x1B[44mDEBUG\x1B[0m] [\x1B[30;47m{}\x1B[0m] [{:%Y-%m-%d %H:%M:%S}] Log", std::this_thread::get_id(), fixedTime); // NOSONAR
    EXPECT_EQ(line, tester);
    std::getline(file, line);
    tester = std::format("[\x1B[42mINFO\x1B[0m] [\x1B[30;47m{}\x1B[0m] [{:%Y-%m-%d %H:%M:%S}] Log", std::this_thread::get_id(), fixedTime); // NOSONAR
    EXPECT_EQ(line, tester);
    std::getline(file, line);
    tester = std::format("[\x1B[43mWARNING\x1B[0m] [\x1B[30;47m{}\x1B[0m] [{:%Y-%m-%d %H:%M:%S}] Log", std::this_thread::get_id(), fixedTime); // NOSONAR
    EXPECT_EQ(line, tester);
    std::getline(file, line);
    tester = std::format("[\x1B[41mERROR\x1B[0m] [\x1B[30;47m{}\x1B[0m] [{:%Y-%m-%d %H:%M:%S}] Log", std::this_thread::get_id(), fixedTime); // NOSONAR
    EXPECT_EQ(line, tester);
    std::getline(file, line);
    tester = std::format("[\x1B[31;47mCRITICAL\x1B[0m] [\x1B[30;47m{}\x1B[0m] [{:%Y-%m-%d %H:%M:%S}] Log", std::this_thread::get_id(), fixedTime); // NOSONAR
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
                                std::format("[\x1B[41mERROR\x1B[0m] [\x1B[30;47mError\x1B[0m] [{:%Y-%m-%d %H:%M:%S}] From Error thread", fixedTime), // NOSONAR
                                std::format("[\x1B[44mDEBUG\x1B[0m] [\x1B[30;47mDebug\x1B[0m] [{:%Y-%m-%d %H:%M:%S}] From Debug thread", fixedTime))); // NOSONAR
    }
}

#pragma endregion