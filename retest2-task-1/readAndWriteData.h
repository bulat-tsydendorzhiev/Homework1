#pragma once

#include "queue.h"

typedef enum
{
    success,
    errorOpening
} ErrorCode;

// Get integer numbers from file
int getDataFromFile(const char* const fileName, Queue* const lessQueue, Queue* const middleQueue, Queue* const greaterQueue,
    const int lessNumber, const int greaterNumber);

// Write integer number to file
int writeNumbersToFile(const char* const fileName, Queue* const lessQueue, Queue* const middleQueue, Queue* const greaterQueue);
