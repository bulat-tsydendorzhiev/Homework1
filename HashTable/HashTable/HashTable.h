#pragma once

#include <stdbool.h>
#include <stdlib.h>

// Hash table
typedef struct HashTable HashTable;

// Create a hash table with capacity equals 4
HashTable* createHashTable(void);

// Add value in hash table
// if the value is not in the hash table, add a new one
// else increase the counter
bool addValue(HashTable* table, const char* const value);

// Check availability of value in the hash table
// return true if value exist
bool tableContains(const HashTable* const table, const char* const value);

// Print hash table values and their 
void printHashTable(const HashTable* const table);

// Delete hash table
void deleteHashTable(HashTable** table);

// Return load factor of hash table
float getLoadFactor(const HashTable* const table);

// Return length of bucket with max length
size_t getMaxBucketLength(const HashTable* const table);

// Return average length of buckets
float getAverageBucketLength(const HashTable* const table);
