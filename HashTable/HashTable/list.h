#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef enum
{
    uniqueValue,
    notUniqueValue,
    outOfMemory
} ListError;

// List
typedef struct List List;

// Create list
List* createList(void);

// Check emptiness of list
// return true if list is empty;
bool listIsEmpty(const List* const list);

// Check availability of value in the list
// return true if value exist
bool listContains(List* const list, const char* const value);

// Add value in list
// if the value is not in the list, add a new one
// else increase the counter of amountOfValue
ListError addValueToList(List* const list, const char* const value, const size_t amountOfValue);

// Return length of list
size_t getLength(const List* const list);

// Return amountOfValue of values in list element
size_t getAmountOfValue(const List* const list);

// Return list head value
const char* getHeadValue(const List* const list);

// Remove list head value
void deleteHeadValue(List* const list);

// Print value and count of it
void printList(List* list);

// Delete list
void deleteList(List** list);
