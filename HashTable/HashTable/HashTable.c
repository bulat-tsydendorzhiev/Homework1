#include <stdlib.h>
#include <stdio.h>

#include "hashTable.h"
#include "list.h"

typedef List Bucket;

struct HashTable
{
    int size;
    int numberOfElements;
    Bucket** buckets;
};

static bool createBuckets(HashTable* table)
{
    table->buckets = (Bucket**)calloc(table->size, sizeof(Bucket*));
    if (table->buckets == NULL)
    {
        return true;
    }

    for (size_t i = 0; i < table->size; ++i)
    {
        table->buckets[i] = createList();
        if (table->buckets[i] == NULL)
        {
            return true;
        }
    }
    return false;
}

HashTable* createHashTable(void)
{
    HashTable* table = calloc(1, sizeof(HashTable));
    if (table == NULL)
    {
        return NULL;
    }
    table->size = 4;
    const bool errorCreateOfBuckets = createBuckets(table);
    if (errorCreateOfBuckets)
    {
        return NULL;
    }
    return table;
}

static int hashFunction(const char* const value)
{
    int hashValue = 0;
    int power31 = 1;
    for (size_t i = 0; value[i] != '\0'; ++i)
    {
        hashValue = (hashValue + (value[i] - 'a' + 1) * power31) % INT_MAX;
        power31 = (power31 * 31) % INT_MAX;
    }
    return abs(hashValue);
}

static Bucket* createTempBucket(HashTable* table)
{
    Bucket* tempBucket = createList();
    if (tempBucket == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < table->size; i++)
    {
        while (!listIsEmpty(table->buckets[i]))
        {
            const int errorAddition = addValueToList(tempBucket, getHeadValue(table->buckets[i]), getFrequency(table->buckets[i]));
            if (errorAddition < 0)
            {
                return NULL;
            }
            deleteHeadValue(table->buckets[i]);
        }
        deleteList(&table->buckets[i]);
    }

    return tempBucket;
}

static bool rehash(HashTable* table)
{
    Bucket* tempBucket = createTempBucket(table);
    if (tempBucket == NULL)
    {
        return;
    }

    table->size = table->size << 1;
    createBuckets(table);
    while (!listIsEmpty(tempBucket))
    {
        char* value = getHeadValue(tempBucket);
        const int errorAdition = addValueToList(table->buckets[hashFunction(value) % table->size], value, getFrequency(tempBucket));
        if (errorAdition < 0)
        {
            return true;
        }
        deleteHeadValue(tempBucket);
    }
    deleteList(&tempBucket);
    return 0;
}

bool addValue(HashTable* table, const char* const value)
{
    const int addNewValue = addValueToList(table->buckets[hashFunction(value) % table->size], value, 1);
    if (addNewValue > 0)
    {
        ++table->numberOfElements;
    }
    else if (addNewValue < 0)
    {
        return true;
    }

    if (getLoadFactor(table) >= 1.0)
    {
        const int errorRehash = rehash(table);
        if (errorRehash)
        {
            deleteHashTable(&table);
            return true;
        }
    }
    return false;
}

bool tableContains(const HashTable* const table, const char* const value)
{
    return listContains(table->buckets[hashFunction(value) % table->size], value);
}

void printHashTable(const HashTable* const table)
{
    for (size_t i = 0; i < table->size; i++)
    {
        if (!listIsEmpty(table->buckets[i]))
        {
            printList(table->buckets[i]);
        }
    }
}

void deleteHashTable(HashTable** table)
{
    for (size_t i = 0; i < (*table)->size; i++)
    {
        deleteList(&(*table)->buckets[i]);
    }
    free(*table);
    *table = NULL;
}

float getLoadFactor(const HashTable* const table)
{
    return (float)table->numberOfElements / table->size;
}

int getMaxBucketLength(const HashTable* const table)
{
    int maxLength = 0;
    for (size_t i = 0; i < table->size; i++)
    {
        maxLength = max(maxLength, getLength(table->buckets[i]));
    }
    return maxLength;
}

float getAverageBucketLength(const HashTable* const table)
{
    int sumOfLengths = 0;
    int notEmptyBucketNumber = 0;
    for (size_t i = 0; i < table->size; i++)
    {
        sumOfLengths += getLength(table->buckets[i]);
        notEmptyBucketNumber += !listIsEmpty(table->buckets[i]);
    }
    return (notEmptyBucketNumber == 0) ? 0 : (float)sumOfLengths / notEmptyBucketNumber;
}