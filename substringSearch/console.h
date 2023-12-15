#pragma once

// success: everything is alright;
// outOfMemory: lack of memory happened
typedef enum
{
    success,
    outOfMemory = 2
} ErrorCode;

// Console
int runProgram(void);
