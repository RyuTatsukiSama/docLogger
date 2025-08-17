#include <gtest/gtest.h>
#include "../src/Logger/rLogger.h"

TEST(rLogSeverityTest, LogTest)
{
	EXPECT_EQ(rLogSeverity::Log.value, 0);
}

TEST(rLogSeverityTest, DebugTest)
{
	EXPECT_EQ(rLogSeverity::Debug.value, 1);
}

TEST(rLogSeverityTest, InfoTest)
{
	EXPECT_EQ(rLogSeverity::Info.value, 2);
}

TEST(rLogSeverityTest, WarningTest)
{
	EXPECT_EQ(rLogSeverity::Warning.value, 3);
}

TEST(rLogSeverityTest, ErrorTest)
{
	EXPECT_EQ(rLogSeverity::Error.value, 4);
}

TEST(rLogSeverityTest, CriticalTest)
{
	EXPECT_EQ(rLogSeverity::Critical.value, 5);
}
