#include <gtest/gtest.h>
#include "../src/rLogger/rLoggerOptions.h"

TEST(optionsTest, defaultsTest)
{
    rLoggerOptions opts = rLoggerOptions::defaults;
    EXPECT_EQ(opts.threadName, "Main");
    EXPECT_EQ(opts.outputConsole, true);
    EXPECT_EQ(opts.outputFile, true);
    EXPECT_EQ(opts.fileName, "");
}