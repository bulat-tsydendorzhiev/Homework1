#pragma once

#include <stdbool.h>

typedef enum
{
	okCircularList,
	circularListIsEmptyError,
	circularListOutOfMemory,
	circularListNonExistentElement
} CircularListError;

typedef struct CircularList CircularList;

// Function to create circle list
CircularListError createCircularList(CircularList** circularList);

// Function to check circle list emptiness
bool circularListisEmpty(CircularList* circularList);

// Function to add value at the end of circle list
CircularListError append(CircularList** circularList, const int value);

// Function to delete value from circle list by its position number
CircularListError deletePosition(CircularList** circularList, const int positionNumber);

// Function to check whether the one node left, return true if it is
bool onlyOneLeft(CircularList* circularList);

// Function to get a value of head node
int getHeadValue(CircularList* circularList);

// Function to clear circle list
void clearCircularList(CircularList** list);

