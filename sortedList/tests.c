#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "tests.h"
#include "sortedList.h"

static bool addTestingValues(SortedList* list, const int* const pushingValues, const size_t numberOfPushingValues)
{
    for (size_t i = 0; i < numberOfPushingValues; i++)
    {
        const int errorPush = addValue(list, pushingValues[i]);
        if (errorPush)
        {
            return false;
        }
    }
    return isSorted(list);
}

static bool deleteTestingValues(SortedList* list, const int* const popingValues, const size_t numberOfPopingValues)
{
    for (size_t i = 0; i < numberOfPopingValues; i++)
    {
        const int errorPop = deleteValue(list, popingValues[i]);
        if (errorPop)
        {
            return false;
        }
    }
    return isSorted(list);
}

static bool runAddingValuesTest(void)
{
    SortedList* list = createSortedList();
    if (list == NULL)
    {
        return false;
    }

    const int pushingValues[] = { 3, -1, 4, 1, 5, 9, 2, 6, 5, 0 };
    const size_t numberOfPushingValues = sizeof(pushingValues) / sizeof(pushingValues[0]);
    const bool errorPush = addTestingValues(list, pushingValues, numberOfPushingValues);

    deleteSortedList(&list);
    return errorPush;
}

static bool runDeletingValuesTest(void)
{
    SortedList* list = createSortedList();
    if (list == NULL)
    {
        return false;
    }

    const int pushingValues[] = { 3, -1, 4, 1, 5, 9, 2, 6, 5, 0 };
    const size_t numberOfPushingValues = sizeof(pushingValues) / sizeof(pushingValues[0]);
    const bool successPush = addTestingValues(list, pushingValues, numberOfPushingValues);
    if (!successPush)
    {
        deleteSortedList(&list);
        return false;
    }

    const int popingValues[] = { -1, 0, 5, 9 };
    const size_t numberOfPopingValues = sizeof(popingValues) / sizeof(popingValues[0]);
    const bool errorPop = deleteTestingValues(list, popingValues, numberOfPopingValues);

    deleteSortedList(&list);
    return errorPop;
}

bool tests(void)
{
    if (!runAddingValuesTest())
    {
        printf("Adding value test failed\n");
        return false;
    }
    if (!runDeletingValuesTest())
    {
        printf("Deleting value test failed\n");
        return false;
    }
    return true;
}