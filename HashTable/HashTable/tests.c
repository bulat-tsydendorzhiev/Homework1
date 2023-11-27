#include <stdlib.h>
#include <string.h>

#include "tests.h"
#include "list.h"
#include "hashTable.h"

static bool addValueToListTest(List* list, const char values[][4], const size_t numberOfValues)
{
    for (size_t i = 0; i < numberOfValues; ++i)
    {
        addValueToList(list, values[i], 1);
        if (!listContains(list, values[i]))
        {
            deleteList(&list);
            return true;
        }
    }
    return false;
}

static bool deleteHeadValueFromListTest(List* list, const char values[][4], const size_t numberOfValues)
{
    for (size_t i = 0; i < numberOfValues; i++)
    {
        deleteHeadValue(list);
        if (i + 1 == numberOfValues)
        {
            return getHeadValue(list) != NULL;
        }
        if (strcmp(getHeadValue(list), values[i + 1]) != 0)
        {
            return true;
        }
    }
}

static bool testForList(void)
{
    List* list = createList();
    if (list == NULL)
    {
        deleteList(&list);
        return true;
    }

    const char values[][4] = { "1st", "2nd", "3rd", "4th", "5th" };
    const size_t numberOfValues = sizeof(values) / sizeof(values[0]);

    const bool test1Failed = addValueToListTest(list, values, numberOfValues);
    if (test1Failed)
    {
        deleteList(&list);
        return true;
    }

    const bool test2Failed = deleteHeadValueFromListTest(list, values, numberOfValues);
    if (test2Failed)
    {
        deleteList(&list);
        return true;
    }

    deleteList(&list);
    return false;
}

static bool addValueToHashTableTest(void)
{
    HashTable* table = createHashTable();
    if (table == NULL)
    {
        deleteHashTable(&table);
        return true;
    }

    const char addingValues[][2] = { "1", "2", "3", "4", "1", "6" };
    const size_t length = sizeof(addingValues) / sizeof(addingValues[0]);
    for (size_t i = 0; i < length; i++)
    {
        addValue(table, addingValues[i]);
        if (!tableContains(table, addingValues[i]))
        {
            deleteHashTable(&table);
            return true;
        }
    }
    deleteHashTable(&table);
    return false;
}

static bool lengthOfBucketTest(void)
{
    HashTable* table = createHashTable();
    if (table == NULL)
    {
        deleteHashTable(&table);
        return true;
    }

    const char addingValues[][123] = { "sad", "me", "she", "she", "loves", "him" };
    const size_t length = sizeof(addingValues) / sizeof(addingValues[0]);
    for (size_t i = 0; i < length; i++)
    {
        addValue(table, addingValues[i]);
    }

    const int maxLengthOfBucket = getMaxBucketLength(table);
    const float averageLength = getAverageBucketLength(table);
    const float loadFactor = getLoadFactor(table);

    deleteHashTable(&table);
    return loadFactor != 0.625 || averageLength != 1.25 || maxLengthOfBucket != 2;
}

static bool testForHashTable(void)
{
    const bool test1Failed = addValueToHashTableTest();
    if (test1Failed)
    {
        return true;
    }

    const bool test2Failed = lengthOfBucketTest();
    if (test2Failed)
    {
        return true;
    }

    return false;
}

bool tests(void)
{
    const bool listTestFailed = testForList();
    if (listTestFailed)
    {
        return true;
    }

    const bool hashTableTestFailed = testForHashTable();
    if (hashTableTestFailed)
    {
        return true;
    }

    return false;
}
