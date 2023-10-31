#pragma once

typedef enum
{
	ok,
	listIsEmpty,
	outOfMemory,
	deletingANonExistentElement
} ErrorCode;

// Node of the sorted list
typedef struct Node Node;

// Function to push value and preserves sorting
ErrorCode pushValue(Node** list, const int value);

// Function to delete value and preserves sorting
ErrorCode deleteValue(Node** list, const int value);

// Function to print sorted list
void printList(Node* list);

// Function to clear list
ErrorCode clearList(Node** list);