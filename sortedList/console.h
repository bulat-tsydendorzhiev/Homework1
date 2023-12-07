#pragma once

// success: if everything is alright;
// listError: if error because of list occurred
typedef enum
{
    success = 0,
    listError = 2,
} ConsoleErrorCodes;

// Run the program
ConsoleErrorCodes runProgram(void);
