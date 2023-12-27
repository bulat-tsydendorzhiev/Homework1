#include <stdio.h>
#include <limits.h>

#include "HashTable.h"
#include "List.h"

typedef List Bucket;

#define MOD INT_MAX

struct HashTable
{
    size_t size;
    size_t numberOfElements;
    Bucket** buckets;
};

static Bucket** createBuckets(const size_t tableSize)
{
    Bucket** newBuckets = (Bucket**)calloc(tableSize, sizeof(Bucket*));
    if (newBuckets == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < tableSize; ++i)
    {
        newBuckets[i] = createList();
        if (newBuckets[i] == NULL)
        {
            for (size_t j = 0; j < i; ++j)
            {
                deleteList(&newBuckets[j]);
            }
            return NULL;
        }
    }
    return newBuckets;
}

HashTable* createHashTable(void)
{
    HashTable* table = (HashTable*)calloc(1, sizeof(HashTable));
    if (table == NULL)
    {
        return NULL;
    }

    table->size = 4;
    table->buckets = createBuckets(table->size);
    if (table->buckets == NULL)
    {
        free(table);
        return NULL;
    }
    return table;
}

static size_t calculateHash(const char* const value)
{
    size_t hashValue = 0;
    size_t power31 = 1;
    for (size_t i = 0; value[i] != '\0'; ++i)
    {
        hashValue = (hashValue + (value[i] - 'a' + 1) * power31) % MOD;
        power31 = (power31 * 31) % MOD;
    }
    return hashValue;
}

static bool rehash(HashTable* table)
{
    const size_t newLength = table->size * 2;
    Bucket** newBuckets = createBuckets(table->size * 2);
    if (newBuckets == NULL)
    {
        return false;
    }

    for (size_t i = 0; i < table->size; ++i)
    {
        while (!listIsEmpty(table->buckets[i]))
        {
            const char* tableBucketValue = getHeadValue(table->buckets[i]);
            const ListError errorAddition = addValueToList(newBuckets[calculateHash(tableBucketValue) % newLength], tableBucketValue, getAmountOfValue(table->buckets[i]));
            if (errorAddition == outOfMemory)
            {
                return false;
            }
            deleteHeadValue(table->buckets[i]);
        }
        deleteList(&table->buckets[i]);
    }

    table->size = newLength;
    table->buckets = newBuckets;
    return true;
}

bool addValue(HashTable* table, const char* const value)
{
    const ListError errorAdding = addValueToList(table->buckets[calculateHash(value) % table->size], value, 1);
    if (errorAdding == uniqueValue)
    {
        ++table->numberOfElements;
    }
    else if (errorAdding == outOfMemory)
    {
        return false;
    }

    if (getLoadFactor(table) >= 1.0)
    {
        const bool successfulRehash = rehash(table);
        if (!successfulRehash)
        {
            return false;
        }
    }
    return true;
}

bool tableContains(const HashTable* const table, const char* const value)
{
    return listContains(table->buckets[calculateHash(value) % table->size], value);
}

void printHashTable(const HashTable* const table)
{
    for (size_t i = 0; i < table->size; ++i)
    {
        if (!listIsEmpty(table->buckets[i]))
        {
            printList(table->buckets[i]);
        }
    }
}

void deleteHashTable(HashTable** table)
{
    for (size_t i = 0; i < (*table)->size; ++i)
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

size_t getMaxBucketLength(const HashTable* const table)
{
    size_t maxLength = 0;
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
    for (size_t i = 0; i < table->size; ++i)
    {
        sumOfLengths += getLength(table->buckets[i]);
        notEmptyBucketNumber += !listIsEmpty(table->buckets[i]);
    }
    return (notEmptyBucketNumber == 0) ? 0 : (float)sumOfLengths / notEmptyBucketNumber;
}