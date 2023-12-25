#pragma once

#include <stdbool.h>

// Circular list
typedef struct CircularList CircularList;

// Create circular list
CircularList* createCircularList(void);

// Check circular list emptiness
bool circularListIsEmpty(CircularList* circularList);

// Add value at the end of the circular list;
// return false if it fails to add an element to the list
bool append(CircularList* circularList, const int value);

// Delete value from circular list by its position number
void deletePosition(CircularList* circularList, const int positionNumber);

// Check whether the one node left;
// return true if it is
bool isOnlyOneLeft(const CircularList*const circularList);

// Return a value of head node
int getHeadValue(const CircularList*const circularList);

// Clear circular list
void clearCircularList(CircularList** const list);
