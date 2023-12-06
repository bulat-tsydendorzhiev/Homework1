#pragma once

#include <stdio.h>
#include <stdbool.h>

typedef enum
{
    ok,
    scanError,
    outOfMemoryError
} DataInitError;

// Loading from file;
// Return "ok" if there are no errors; "scanError" if not enough value in stream; "outOfMemoryError" if out of memory happened
DataInitError dataInit(FILE* file, size_t* numberOfCities, size_t*** distanceBetweenCities,
    size_t* numberOfCapitals, size_t*** states, bool** isCityFree);

// free all memory we used
void freeMemory(size_t*** const graph, const size_t numberOfCities, size_t*** const states, const size_t numberOfCapitals, bool** const visited);
