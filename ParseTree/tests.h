#pragma once

typedef enum
{
    testsPassed,
    testFailed,
    buildingError
} TestErrorCode;

// Tests for parse tree
TestErrorCode tests(void);