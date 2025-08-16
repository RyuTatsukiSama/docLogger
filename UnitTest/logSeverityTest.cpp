#include <gtest/gtest.h>
#include "../src/Logger/rLogger.h"

TEST(rLogSeverityTest, LogTest)
{
	EXPECT_EQ(rLogSeverity::LOG.value, 0);
}

TEST(rLogSeverityTest, DebugTest)
{
	EXPECT_EQ(rLogSeverity::DEBUG.value, 1);
}

TEST(rLogSeverityTest, InfoTest)
{
	EXPECT_EQ(rLogSeverity::INFO.value, 2);
}

TEST(rLogSeverityTest, WarningTest)
{
	EXPECT_EQ(rLogSeverity::WARNING.value, 3);
}

TEST(rLogSeverityTest, ErrorTest)
{
	EXPECT_EQ(rLogSeverity::ERROR.value, 4);
}

TEST(rLogSeverityTest, CriticalTest)
{
	EXPECT_EQ(rLogSeverity::CRITICAL.value, 5);
}
