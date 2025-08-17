#include <gtest/gtest.h>
#define RTESTING
#include "../src/Logger/rLogger.h"

TEST(FormatLogTest, TestOne) // ! Change the test name
{
    rLogger testLogger;

    EXPECT_EQ(testLogger.GetFormatLog(rLogSeverity::LOG, "This is a log level"), std::format("[LOG] [{}] [Main] This is a log level", time(NULL)));
}