#pragma once

typedef enum
{
	testPassed,
	test1Failed,
	test2Failed,
	test3Failed,
	test4Failed,
	test5Failed,
} TestErrorCode;

// Tests to check working of the sorted list methods
TestErrorCode tests(void);
