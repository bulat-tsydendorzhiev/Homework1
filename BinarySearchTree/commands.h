#pragma once

typedef enum
{
    successfullCommand,
    outOfMemoryCommands
} comandError;

// Диалоговое окно для пользователя
comandError commands(void);
