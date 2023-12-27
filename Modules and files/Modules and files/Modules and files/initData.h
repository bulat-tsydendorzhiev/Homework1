#pragma once

#include <stdlib.h>

typedef enum
{
    success,
    scanError,
    outOfMemory,
    openningFileError,
    nullFileName
} ErrorCode;

// Read array from file
ErrorCode readArrayFromFile(const char* const fileName, int** const array, size_t* const arrayLength);
