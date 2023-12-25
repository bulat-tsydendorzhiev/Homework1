#pragma once

typedef enum
{
    ok,
    deletingNonExistentElement,
    outOfMemory
} SortedListErrorCode;

typedef enum
{
    exitCommand,
    addValueToList,
    deleteValueFromList,
    printList
} Command;

// Sorted list
typedef struct SortedList SortedList;

// Create sorted list
SortedList* createSortedList(void);

// Add a value so that the list is sorted
SortedListErrorCode addValue(SortedList* const sortedList, const int value);

// Delete list value
SortedListErrorCode deleteValue(SortedList* const sortedList, const int value);

// Print sorted list values
void printSortedList(const SortedList* const sortedList);

// Delete sorted list
void deleteSortedList(SortedList** sortedList);

// Сheck list for sortingж
// Return true if list is sorted
bool isSorted(const SortedList* const list);

// Print commands for user
void printCommands(void);
