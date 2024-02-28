#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "tests.h"
#include "List.h"
#include "HashTable.h"

#define NUMBER_OF_ADDING_VALUES 
#define MAX_LENGTH_OF_TEST_STRING 10

static bool runAddValueToListTest(List* list, const char values[][MAX_LENGTH_OF_TEST_STRING], const size_t numberOfValues)
{
    for (size_t i = 0; i < numberOfValues; ++i)
    {
        const ListError errorAdding = addValueToList(list, values[i], 1);
        if (errorAdding == outOfMemory)
        {
            return false;
        }
        if (!listContains(list, values[i]))
        {
            return false;
        }
    }
    return true;
}

static bool runDeleteHeadValueFromListTest(List* list, const char values[][MAX_LENGTH_OF_TEST_STRING], const size_t numberOfValues)
{
    for (size_t i = 0; i < numberOfValues; ++i)
    {
        deleteHeadValue(list);
        if (i + 1 == numberOfValues)
        {
            return getHeadValue(list) == NULL;
        }
        if (strcmp(getHeadValue(list), values[i + 1]) != 0)
        {
            return false;
        }
    }
    return true;
}

static bool runTestsForList(void)
{
    List* list = createList();
    if (list == NULL)
    {
        return false;
    }

    const char values[][MAX_LENGTH_OF_TEST_STRING] = { "1st", "2nd", "3rd", "4th", "5th" };
    const size_t numberOfValues = sizeof(values) / sizeof(values[0]);

    const bool addValueToListTestPassed = runAddValueToListTest(list, values, numberOfValues);
    if (!addValueToListTestPassed)
    {
        printf("Adding value to list test failed\n");
        deleteList(&list);
        return false;
    }

    const bool deleteHeadValueFromListTestPassed = runDeleteHeadValueFromListTest(list, values, numberOfValues);
    if (!deleteHeadValueFromListTestPassed)
    {
        printf("Deleting value to list test failed\n");
        deleteList(&list);
        return false;
    }

    deleteList(&list);
    return true;
}

static bool runAddValueToHashTableTest(void)
{
    HashTable* table = createHashTable();
    if (table == NULL)
    {
        return false;
    }

    const char addingValues[][MAX_LENGTH_OF_TEST_STRING] = { "1", "2", "3", "4", "1", "6" };
    const size_t length = sizeof(addingValues) / sizeof(addingValues[0]);

    for (size_t i = 0; i < length; ++i)
    {
        const bool successfulAdding = addValue(table, addingValues[i]);
        if (!successfulAdding)
        {
            deleteHashTable(&table);
            return false;
        }
        if (!tableContains(table, addingValues[i]))
        {
            deleteHashTable(&table);
            return false;
        }
    }

    deleteHashTable(&table);
    return true;
}

// Tests for function of getting max, average length of bucket and load factor
static bool runLengthOfBucketTest(void)
{
    HashTable* table = createHashTable();
    if (table == NULL)
    {
        return false;
    }

    const char addingValues[][MAX_LENGTH_OF_TEST_STRING] = { "sad", "me", "she", "she", "loves", "him" };
    const size_t length = sizeof(addingValues) / sizeof(addingValues[0]);
    for (size_t i = 0; i < length; ++i)
    {
        const bool successfulAdding = addValue(table, addingValues[i]);
        if (!successfulAdding)
        {
            deleteHashTable(&table);
            return false;
        }
    }

    const size_t maxLengthOfBucket = getMaxBucketLength(table);
    const float averageLength = getAverageBucketLength(table);
    const float loadFactor = getLoadFactor(table);

    deleteHashTable(&table);
    return loadFactor == 0.625 || averageLength == 1.25 || maxLengthOfBucket == 2;
}

static bool runTestsForHashTable(void)
{
    const bool successfulAdding = runAddValueToHashTableTest();
    if (!successfulAdding)
    {
        printf("Adding value to hash table test failed\n");
        return false;
    }

    const bool successfulLengthsTest = runLengthOfBucketTest();
    if (!successfulLengthsTest)
    {
        printf("Test for lengths of hash table failed\n");
        return false;
    }

    return true;
}

bool runTests(void)
{
    const bool listTestPassed = runTestsForList();
    if (!listTestPassed)
    {
        return false;
    }

    const bool hashTableTestPassed = runTestsForHashTable();
    if (!hashTableTestPassed)
    {
        return false;
    }

    return true;
}
