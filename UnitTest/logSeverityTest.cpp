#include <gtest/gtest.h>
#include "../src/Logger/Logger.h"
using namespace doc;

///@brief Unit tests for LoggerSeverity struct

TEST(rLogSeverityTest, LogTest)
{
	EXPECT_EQ(LoggerSeverity::Trace.value, 0);
}

TEST(rLogSeverityTest, DebugTest)
{
	EXPECT_EQ(LoggerSeverity::Debug.value, 1);
}

TEST(rLogSeverityTest, InfoTest)
{
	EXPECT_EQ(LoggerSeverity::Info.value, 2);
}

TEST(rLogSeverityTest, WarningTest)
{
	EXPECT_EQ(LoggerSeverity::Warning.value, 3);
}

TEST(rLogSeverityTest, ErrorTest)
{
	EXPECT_EQ(LoggerSeverity::Error.value, 4);
}

TEST(rLogSeverityTest, CriticalTest)
{
	EXPECT_EQ(LoggerSeverity::Critical.value, 5);
}

TEST(rLogSeverityTest, NoneTest)
{
	EXPECT_EQ(LoggerSeverity::None.value, 6);
}