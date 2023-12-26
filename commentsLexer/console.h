#pragma once

typedef enum
{
    success,
    fileOpenningError,
    commentsGettingError = 4
} ConsoleError;

ConsoleError runProgram(void);