#pragma once

// success: if everything is alright;
// listError: if error because of list occurred
typedef enum
{
    success,
    scanError,
    listError,
} ConsoleErrorCodes;

// Run the program
ConsoleErrorCodes runProgram(void);
