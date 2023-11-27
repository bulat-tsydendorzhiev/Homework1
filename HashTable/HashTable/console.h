#pragma once

typedef enum
{
    ok,
    hashTableError,
    openFileError
} ConsoleError;

// Console
// return 0 if everything is alright; 1 if hash table has out of memory error; 2 if error occured during file opening
ConsoleError console(void);
