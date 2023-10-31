#pragma once

typedef enum
{
	testPassed,
	testFailed
} TestErrorCode;

// Tests for shunting yard working
TestErrorCode tests(void);