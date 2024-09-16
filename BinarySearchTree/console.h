#pragma once

typedef enum
{
    success,
    lackOfMemory = 2
} ConsoleError;

// Works with the user
ConsoleError runProgram(void);
