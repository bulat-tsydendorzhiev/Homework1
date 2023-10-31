#pragma once
#include <stdbool.h>
#include "list.h"

#define MAX_NAME_LENGTH 50
#define MAX_PHONE_NUMBER_LENGTH 20

typedef enum
{
	okList,
	listIsEmpty,
	listOutOfMemory,
	listOpenFileError
} ListErrorCode;

typedef struct Node Node;

// Function to add name and phone number at the end of the list
ListErrorCode append(Node** list, const char* name, const char* phoneNumber);

//Function to load contacts from file
ListErrorCode loadData(Node** list, const char* filename);

//Function to get next node
Node* getNextNode(Node* node, ListErrorCode* errorCode);

// Function to print contacts in format "name - phone number"
void printList(Node* list);

// Function to clear list
ListErrorCode clearList(Node** list);

// Function to change the value of next node
ListErrorCode changeNextNode(Node** node, Node* changeValue);

// Function to get node field( name or phone number )
char* getField(Node* node, int gettingField);