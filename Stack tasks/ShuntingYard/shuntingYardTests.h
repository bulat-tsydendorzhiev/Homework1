#pragma once

typedef enum
{
	testsPassed,
	testFailed,
	testOutOfMemoryError
} TestErrorCode;

// Tests for shunting yard working
TestErrorCode tests(void);