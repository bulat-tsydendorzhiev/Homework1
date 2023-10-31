#pragma once

#include <stdbool.h>

// Error codes for int stack results
typedef enum IntErrorCode
{
	okIntStack,
	IntStackIsEmpty,
	outOfMemoryIntStack
}IntErrorCode;

// Stack that consists of int values
typedef struct IntStack IntStack;

// Function to check emptiness of the int stack
bool intStackIsEmpty(IntStack* head);

// Function to push int element to the int stack
IntErrorCode pushInt(IntStack** head, const int value);

// Function to pop int element from the int stack
IntErrorCode popInt(IntStack** head);

// Function to clear int stack
IntErrorCode clearIntStack(IntStack** head);

// Function to return top element of the int stack
int topInt(IntStack* head, IntErrorCode* errorCode);