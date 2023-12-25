#pragma once

typedef enum
{
    success,
    scanError
} ConsoleError;

// Console
ConsoleError runProgram(void);
