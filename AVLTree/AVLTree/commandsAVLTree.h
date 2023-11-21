#pragma once

typedef enum
{
    successfullCommand,
    outOfMemoryCommands,
    errorInput
} CommandError;

// User Dialog Box
CommandError commands(void);
