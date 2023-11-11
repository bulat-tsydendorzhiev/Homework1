#pragma once

typedef enum
{
    outOfMemory = -2,
    testFailed,
    testsPassed,
    addTestFailed,
    findKeyTestFailed,
    getValueTestFailed,
    deleteTestFailed,
} TestErrorCode;

// Tests to check the working of the binary search tree
TestErrorCode tests(void);
