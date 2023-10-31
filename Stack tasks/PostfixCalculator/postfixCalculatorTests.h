#pragma once

typedef enum ErrorTest
{
	testPassed,
	testFailed
}ErrorTest;

// Tests for postfix calculator working
ErrorTest tests(void);