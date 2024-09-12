#pragma once

// success: everything is alright;
// circularListError: error occurred because of circular list;
// wrongInput: err
typedef enum
{
    circularListError = -1,
    success = 0,
    wrongInput = 1
} ConsoleErrorCode;

// Run the program
ConsoleErrorCode runProgram(void);