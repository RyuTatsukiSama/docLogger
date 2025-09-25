#include <gtest/gtest.h>
#include "../src/rLogger/rLoggerOptions.h"

// Check if the default value or the options are the good ones
TEST(optionsTest, defaultsTest)
{
    rLoggerOptions opts = rLoggerOptions::Builder().build();
    EXPECT_EQ(opts.isOutputConsole(), true);
    EXPECT_EQ(opts.isOutputFile(), true);

    // Recreate the name of the file, like in the builder
    std::chrono::time_point now = std::chrono::floor<std::chrono::seconds>(opts.getTimeProvider()());
    std::string fileName = std::format("{:%Y-%m-%d_%H-%M-%S}", now);
    EXPECT_EQ(opts.getFileName(), fileName);

    // Check if timeProvider is coherent, with checking if it is in the good range
    std::chrono::system_clock::time_point before = std::chrono::zoned_time{
        std::chrono::current_zone(),
        std::chrono::system_clock::now()};
    std::chrono::system_clock::time_point timeProvider = opts.getTimeProvider()();
    std::chrono::system_clock::time_point after = std::chrono::zoned_time{
        std::chrono::current_zone(),
        std::chrono::system_clock::now()};

    EXPECT_GE(timeProvider, before);
    EXPECT_LE(timeProvider, after);
}

TEST(optionsTest, builderTest)
{
    std::chrono::system_clock::time_point fixedTime = std::chrono::system_clock::from_time_t(0);
    rLoggerOptions opts = rLoggerOptions::Builder()
                              .setOutputConsole(false)
                              .setOutputFile(false)
                              .setFileName("builder_test")
                              .setTimeProvider([=]
                                               { return fixedTime; })
                              .build();

    EXPECT_EQ(opts.isOutputConsole(), false);
    EXPECT_EQ(opts.isOutputFile(), false);
    EXPECT_EQ(opts.getFileName(), "builder_test");
    EXPECT_EQ(opts.getTimeProvider()(), fixedTime);
}