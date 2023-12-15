#pragma once

typedef enum
{
    success,
    outOfMemory = 2
} ErrorCode;

// Console
ErrorCode runProgram(void);
