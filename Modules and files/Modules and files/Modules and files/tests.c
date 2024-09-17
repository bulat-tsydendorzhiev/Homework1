#include <stdio.h>

#include "tests.h"
#include "quickSort.h"
#include "searchMostFrequent.h"
#include "initData.h"

static bool isSorted(const int* const array, const size_t arrayLength)
{
    if (arrayLength == 1)
    {
        return true;
    }
    for (size_t i = 1; i < arrayLength; ++i)
    {
        if (array[i - 1] > array[i])
        {
            return false;
        }
    }
    return true;
}

static bool runSortTest(void)
{
    int testArrays[][20] = { {1},
                        {5, 4, 3, 2, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                        {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
                        {1, 3, 2, 0, -1, 5, 6, 7, 2, 9, -12, 68, 37, 21, 99, 214, 62, 63, 12, 0} };
    const size_t testArraysLengths[] = { 1, 5, 15, 15, 20 };

    for (size_t i = 0; i < 5; ++i)
    {
        quickSort(testArrays[i], 0, testArraysLengths[i] - 1);
        if (!isSorted(testArrays[i], testArraysLengths[i]))
        {
            return false;
        }
    }
    return true;
}

static bool runTestForSearching(void)
{
    const char testFiles[][10] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt"};
    const int expectedResults[] = {1, 1, 1, 1};
    const size_t numberOfTests = sizeof(testFiles) / sizeof(testFiles[0]);
    for (size_t i = 0; i < numberOfTests; ++i)
    {
        int* testArray = NULL;
        size_t testArrayLength = 0;
        const int errorCode = readArrayFromFile(testFiles[i], &testArray, &testArrayLength);
        if (errorCode)
        {
            return false;
        }

        quickSort(testArray, 0, testArrayLength - 1);
        const int resultOfSearching = searchMostFrequent(testArray, testArrayLength);
        free(testArray);
        if (resultOfSearching != expectedResults[i])
        {
            return false;
        }
    }
    return true;
}

bool runTests(void)
{
    if (!runSortTest())
    {
        printf("Test for sorting failed\n");
        return false;
    }
    if (!runTestForSearching())
    {
        printf("Test for searching failed\n");
        return false;
    }
    return true;
}