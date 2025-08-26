#include <gtest/gtest.h>
#include "../src/rLogger/rLogger.h"

#pragma region FormatLogTest

static std::string formatedMessage;

void FormatLogTester(std::string _formatedMessage)
{
    formatedMessage = _formatedMessage;
}

TEST(rLoggerTest, FormatLogTest)
{
    auto fixedTime = std::chrono::system_clock::from_time_t(0);
    rLogger testLogger(rLoggerOptions::make({.timeProvider = [=]
                                             { return fixedTime; }}));
    testLogger.RegisterLogCallback(FormatLogTester);

    std::string tester = std::format("| [TRACE] [{:%Y-%m-%d %H:%M:%S}] [Main] This is a trace level |", fixedTime);
    testLogger.Log(rLoggerSeverity::Trace, "This is a trace level");
    EXPECT_EQ(formatedMessage, tester);
}

#pragma endregion

TEST(rLoggerTest, CallerTest)
{
    rLogger logger{rLoggerOptions::defaults};

    logger.Caller();
}