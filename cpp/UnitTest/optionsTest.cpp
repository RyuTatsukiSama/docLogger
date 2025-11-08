#include <gtest/gtest.h>
#include <LoggerOptions.h>
using namespace doc;

/// @brief Check if the default value or the options are the good ones
TEST(optionsTest, defaultsTest)
{
    LoggerOptions opts = LoggerOptions::OptionsBuilder().build();
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
    LoggerOptions opts = LoggerOptions::OptionsBuilder()
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

TEST(optionsTest, previousLogTest)
{
    std::string previousLogContent = "This is the previous log";

    if (!std::filesystem::exists("docLogs"))
    {
        std::filesystem::create_directory("docLogs");
    }

    std::ofstream previousTest("docLogs/previous_test.log");

    EXPECT_EQ(previousTest.is_open(), true);
    if (previousTest.is_open())
    {
        previousTest << previousLogContent << std::endl;
    }
    else
    {
        std::cout << "docLogs/previous_test.log is not open" << std::endl;
    }

    previousTest.close();

    LoggerOptions opts = LoggerOptions::OptionsBuilder().setOutputConsole(false).setFileName("previous_test").build();

    std::ifstream previousTestPrevious("docLogs/previous_test-previous.log");

    EXPECT_EQ(previousTestPrevious.is_open(), true);
    if (previousTestPrevious.is_open())
    {
        std::string reader;

        std::getline(previousTestPrevious, reader);

        EXPECT_EQ(previousLogContent, reader);
    }
    else
    {
        std::cout << "docLogs/previous_test-previous.log is not open" << std::endl;
    }
}