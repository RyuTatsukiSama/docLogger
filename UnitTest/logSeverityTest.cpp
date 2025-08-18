#include <gtest/gtest.h>
#include "../src/rLogger/rLogger.h"

TEST(rLogSeverityTest, LogTest)
{
	EXPECT_EQ(rLoggerSeverity::Trace.value, 0);
}

TEST(rLogSeverityTest, DebugTest)
{
	EXPECT_EQ(rLoggerSeverity::Debug.value, 1);
}

TEST(rLogSeverityTest, InfoTest)
{
	EXPECT_EQ(rLoggerSeverity::Info.value, 2);
}

TEST(rLogSeverityTest, WarningTest)
{
	EXPECT_EQ(rLoggerSeverity::Warning.value, 3);
}

TEST(rLogSeverityTest, ErrorTest)
{
	EXPECT_EQ(rLoggerSeverity::Error.value, 4);
}

TEST(rLogSeverityTest, CriticalTest)
{
	EXPECT_EQ(rLoggerSeverity::Critical.value, 5);
}
