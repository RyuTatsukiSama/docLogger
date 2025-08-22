#include <gtest/gtest.h>
#define RTESTING
#include "../src/rLogger/rLogger.h"

TEST(rLoggerTest, FormatLogTest) // ! Change the test name
{
    rLogger testLogger(rLoggerOptions::defaults);

    std::string tester = std::format("[TRACE] [{:%Y-%m-%d %H:%M:%S}] [Main] This is a trace level", std::chrono::zoned_time{
                                                                                                        std::chrono::current_zone(),
                                                                                                        std::chrono::system_clock::now()});
    std::string format = testLogger.GetFormatLog(rLoggerSeverity::Trace, "This is a trace level");
    EXPECT_EQ(format, tester);
}