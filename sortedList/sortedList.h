#pragma once

typedef enum
{
	ok,
	deletingNonExistentElement,
	outOfMemory
} SortedListErrorCode;

// Sorted list
typedef struct SortedList SortedList;

// Create sorted list
SortedList* createSortedList(void);

// Add a value so that the list is sorted
SortedListErrorCode addValue(SortedList* const SortedList, const int value);

// Delete list value
SortedListErrorCode deleteValue(SortedList* const SortedList, const int value);

// Print sorted list values
void printSortedList(const SortedList* const SortedList);

// Delete sorted list
void deleteSortedList(SortedList** SortedList);

// Сheck list for sortingж
// Return true if list is sorted
bool isSorted(const SortedList* const list);