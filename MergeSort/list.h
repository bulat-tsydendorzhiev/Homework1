#pragma once

#include <stdbool.h>

// List
typedef struct List List;

// Create List
List* createList(void);

// Return list length
size_t getListLength(List* list);

// Check list on emptiness
bool listIsEmpty(List* list);

// Add value at the end of the list
bool append(List* list, const char* name, const char* const phoneNumber);

// Return part of contact by key
char* getPartOfContact(const List* const list, const int key);

// Move list element to other list
void moveListElementToOtherList(List* listFrom, List* listTo);

// Print name and phone number
void printList(List* list);

// Delete list
void deleteList(List** list);

// Сheck the list for sorting
bool isSorted(const List* const list, const int key);
