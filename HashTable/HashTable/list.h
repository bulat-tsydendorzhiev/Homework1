#pragma once

#include <stdbool.h>

// List
typedef struct List List;

// Create list
List* createList(void);

// Check emptiness of list
// return true if list is empty;
bool listIsEmpty(List* list);

// Check availability of value in the list
// return true if value exist
bool listContains(List* const list, const char* const value);

// Add value in list;
// if the value is not in the list, add a new one
// else increase the counter of frequency;
// return -1 if out of memory error occured; 1 if the new value in the list appeared else 0
int addValueToList(List* const list, const char* const value, const int frequency);

// Return length of list
int getLength(List* list);

// Return frequency of list element
int getFrequency(List* list);

// Return list head value
char* getHeadValue(List* const list);

// Remove list head value
void deleteHeadValue(List* const list);

// Print value and count of it
void printList(List* list);

// Delete list
void deleteList(List** list);
