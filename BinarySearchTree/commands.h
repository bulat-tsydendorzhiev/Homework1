#pragma once

typedef enum
{
    successfullCommand,
    outOfMemoryCommands
} comandError;

// User Dialog Box
comandError commands(void);
