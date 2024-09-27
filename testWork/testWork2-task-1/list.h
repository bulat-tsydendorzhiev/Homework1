#pragma once

#include <stdbool.h>

typedef enum
{
    okList,
    outOfMemotyList
} ListErrorCode;

typedef struct Node Node;

typedef struct List List;

// Creation list
List* createList(void);

// Check list is empty
// return true if it is
bool listIsEmpty(List* list);

// Add value at the end of the list
ListErrorCode add(List* const head, const int value);

// Check whether we on the last element of the list 
bool isEndOfList(List* list);

// Returns list length
int getLength(List* list);

// delete list element by its
void deleteListElement(List* list, const int index);

// Check availability of element with index
bool contains(List* list, const int index);

// Print counter and value
void printList(List* list);

// Delete list
void deleteList(List** list);
