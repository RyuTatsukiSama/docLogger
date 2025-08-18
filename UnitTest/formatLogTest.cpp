#include <gtest/gtest.h>
#define RTESTING
#include "../src/rLogger/rLogger.h"

TEST(FormatLogTest, TestOne) // ! Change the test name
{
    rLogger testLogger("Main");

    std::string tester = std::format("[LOG] [{}] [Main] This is a log level", time(NULL));
    std::string format = testLogger.GetFormatLog(rLoggerSeverity::Trace, "This is a log level");
    EXPECT_EQ(format, tester);
}