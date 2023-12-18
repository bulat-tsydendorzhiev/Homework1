#pragma once

#include <stdlib.h>

typedef enum
{
    success,
    scanError,
    outOfMemory
} ErrorCode;

// Read array from file;
// return one of error codes
int readArrayFromFile(const char* const fileName, int** const array, size_t* const arrayLength);
