#pragma once

// success: if everything is alright;
// scanError: if user didn't enter number;
// listError: if error because of list occurred
typedef enum
{
    success,
    scanError,
    listError,
} ConsoleErrorCodes;

// Run the program
ConsoleErrorCodes runProgram(void);
