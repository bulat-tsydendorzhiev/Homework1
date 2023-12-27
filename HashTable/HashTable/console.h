#pragma once

typedef enum
{
    success,
    hashTableError,
    openFileError
} ConsoleError;

// Print the frequency of occurrence of words in a file and also load factor, average length of buckets, max length of bucket of hash table
ConsoleError runProgram(void);
