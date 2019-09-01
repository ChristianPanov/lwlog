#pragma once
#include <CppUnitTest.h>

TEST_CLASS(UnitTest)
{
public:
	TEST_CLASS_INITIALIZE(setUp);
	TEST_CLASS_CLEANUP(tearDown);

	TEST_METHOD(format);
	TEST_METHOD(insertPatternData);

	TEST_METHOD(createLogger);
	TEST_METHOD(setLevelVisibility);
	TEST_METHOD(setPattern);
	TEST_METHOD(logMessage);

	TEST_METHOD(backtrace);
	TEST_METHOD(setBacktraceStamp);
	TEST_METHOD(displayBacktrace);
	TEST_METHOD(deleteBacktrace);
};