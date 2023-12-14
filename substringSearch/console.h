#pragma once

// success: everything is alright;
// outOfMemory: lack of memory happened
typedef enum
{
    success,
    testsFailed = -1,
    outOfMemory = -2
} ErrorCode;

// Console
int runProgram(void);
