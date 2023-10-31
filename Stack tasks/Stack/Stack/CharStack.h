#pragma once

#include <stdbool.h>

// Error codes for char stack results
typedef enum CharErrorCode
{
	okCharStack,
	CharStackIsEmpty,
	outOfMemoryCharStack
}CharErrorCode;

// Stack that consists of char values
typedef struct CharStack CharStack;

// Function to check emptiness of the char stack
bool charStackIsEmpty(CharStack* head);

// Function to push char element to the char stack
CharErrorCode pushChar(CharStack** head, const char value);

// Function to pop char element from the char stack
CharErrorCode popChar(CharStack** head);

// Function to clear char stack
CharErrorCode clearCharStack(CharStack** head);

// Function to return top element of the char stack
char topChar(CharStack* head, CharErrorCode* errorCode);