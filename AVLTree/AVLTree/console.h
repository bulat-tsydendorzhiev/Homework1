#pragma once

typedef enum
{
    success,
    errorInput,
    consoleOutOfMemory
} ConsoleError;

// Console
ConsoleError runProgram(void);
