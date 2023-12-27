#pragma once

// success: everything is alright;
// outOfMemory: lack of memory happened
typedef enum
{
    success,
    outOfMemory = 2
} ErrorCode;

// Work with user: user enter substring and print 
ErrorCode runProgram(void);
