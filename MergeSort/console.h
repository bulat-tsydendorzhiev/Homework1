#pragma once

// success: everything is alright;
// listError: error occurred because of list;
// fileError: error occurred while opening the file;
// sortingError: error occurred during merge sort
typedef enum
{
    success = 0,
    listError = 2,
    fileError = 3,
    sortingError = 4
} ConsoleErrorCode;

// Console;
// return DataInitErrorCode or defined error code
ConsoleErrorCode runProgram(void);