#pragma once

#include "list.h"

// successInit: everything is alright;
// scanError: scanning error;
// listOutOfMemory: lack of memory for adding value into the list;
typedef enum
{
    successInit,
    scanError,
    listOutOfMemory
} DataInitErrorCode;

// Data initialization;
// return one of error codes
DataInitErrorCode dataInit(FILE* stream, List* phoneBook);

// Get key from scanning;
// return scanError if wrong input
DataInitErrorCode getKey(int* const key);