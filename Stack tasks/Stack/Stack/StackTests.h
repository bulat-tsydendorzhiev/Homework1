#pragma once

typedef enum
{
	testsPassed,
	test1Failed,
	test2Failed,
	test3Failed
} TestErrorCode;

// Tests for stack for integer values
TestErrorCode intStackTests(void);

// Tests for stack for char values
TestErrorCode charStackTests(void);
