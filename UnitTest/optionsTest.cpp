#include <gtest/gtest.h>
#include "../src/rLogger/rLoggerOptions.h"

TEST(optionsTest, defaultsTest)
{
    rLoggerOptions opts = rLoggerOptions::Builder().build();
    EXPECT_EQ(opts.isOutputConsole(), true);
    EXPECT_EQ(opts.isOutputFile(), true);
    EXPECT_EQ(opts.getFileName(), "");
    // TODO : need to add one for the timeProvider
}