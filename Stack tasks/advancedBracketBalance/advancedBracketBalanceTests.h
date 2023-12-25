#pragma once

typedef enum TestErrorCode
{
    testsPassed,
    testFailed
} TestErrorCode;

// tests for advanced bracket balance
TestErrorCode tests(void);