#pragma once

typedef enum
{
    ok,
    scanError
} ConsoleError;

// Work with user
ConsoleError runProgram(void);
