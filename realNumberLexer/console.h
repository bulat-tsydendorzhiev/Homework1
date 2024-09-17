#pragma once

typedef enum
{
    success,
    outOfMemory = 2
} ErrorCode;

// Work with user: user enters string and the program prints whether a string is a real number
ErrorCode runProgram(void);
