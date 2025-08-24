#include <gtest/gtest.h>
#define RTESTING
#include "../src/rLogger/rLogger.h"

TEST(rLoggerTest, FormatLogTest)
{
    auto fixedTime = std::chrono::system_clock::from_time_t(0);
    rLogger testLogger(rLoggerOptions::make({.timeProvider = [=]
                                             { return fixedTime; }}));

    std::string tester = std::format("| [TRACE] [{:%Y-%m-%d %H:%M:%S}] [Main] This is a trace level |", fixedTime);
    std::string format = testLogger.GetFormatLog(rLoggerSeverity::Trace, "This is a trace level");
    EXPECT_EQ(format, tester);
}

TEST(rLoggerTest, CallerTest)
{
    rLogger logger{rLoggerOptions::defaults};

    logger.Caller();
}