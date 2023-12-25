#pragma once

#include <stdbool.h>

// okCharStack: everything is alright
// emptyIntStackError: int stack is empty
// outOfMemoryCharStack: lack of memory happened
typedef enum IntErrorCode
{
    okIntStack,
    emptyIntStack,
    outOfMemoryIntStack
} IntStackErrorCode;

// Stack that consists of int values
typedef struct IntStack IntStack;

// Check emptiness of the int stack
bool intStackIsEmpty(IntStack* head);

// Push int element to the int stack
IntStackErrorCode pushInt(IntStack** const head, const int value);

// Pop int element from the int stack
IntStackErrorCode popInt(IntStack** const head);

// Clear int stack
IntStackErrorCode clearIntStack(IntStack** const head);

// Return top element of the int stack
int topInt(IntStack* const head, IntStackErrorCode* const errorCode);