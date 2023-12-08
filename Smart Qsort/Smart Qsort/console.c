#include <stdio.h>
#include <stdlib.h>

#include "console.h"
#include "smartQsort.h"

static ErrorCodes initData(int** const array, int* const arrayLength)
{
    printf("Enter array length: ");
    if (scanf_s("%d", arrayLength) != 1 || *arrayLength <= 0)
    {
        return scanError;
    }

    *array = (int*)calloc(*arrayLength, sizeof(int));
    if (*array == NULL)
    {
        return outOfMemory;
    }

    printf("Enter array elements: ");
    for (size_t i = 0; i < *arrayLength; ++i)
    {
        if (scanf_s("%d", &(*array)[i]) != 1)
        {
            free(*array);
            return scanError;
        }
    }
    return ok;
}

ErrorCodes runProgram(void)
{
    int arrayLength = 0;
    int* array = NULL;
    const int errorInit = initData(&array, &arrayLength);
    if (errorInit)
    {
        return errorInit;
    }

    smartQsort(array, 0, arrayLength - 1);
    printSortedArray(array, arrayLength);

    free(array);
    return ok;
}