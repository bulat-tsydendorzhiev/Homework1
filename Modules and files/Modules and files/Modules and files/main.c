#include <stdio.h>

#include "quickSort.h"
#include "searchMostFrequent.h"
#include "initData.h"
#include "tests.h"

#define TESTS_FAILED -1
#define FILE_NAME "input.txt"

int main()
{
    const bool testsPassed = runTests();
    if (!testsPassed)
    {
        return TESTS_FAILED;
    }

    int* array = NULL;
    size_t arrayLength = 0;
    const ErrorCode errorCode = readArrayFromFile(FILE_NAME, &array , &arrayLength);
    if (errorCode)
    {
        return errorCode;
    }

    quickSort(array, 0, arrayLength - 1);
    const int mostFrequentElement = searchMostFrequent(array, arrayLength);

    printf("Most frequent element in array: %d\n", mostFrequentElement);

    free(array);
    return success;
}