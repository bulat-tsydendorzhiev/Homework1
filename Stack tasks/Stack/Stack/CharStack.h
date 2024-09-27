#pragma once

#include <stdbool.h>

// okCharStack: everything is alright
// emptyCharStackError: char stack is empty
// outOfMemoryCharStack: lack of memory happened
typedef enum CharErrorCode
{
    okCharStack,
    emptyCharStack,
    outOfMemoryCharStack
} CharStackErrorCode;

// Stack that consists of char values
typedef struct CharStack CharStack;

// Check emptiness of the char stack
bool charStackIsEmpty(CharStack* head);

// Push char value to the char stack
CharStackErrorCode pushChar(CharStack** const head, const char value);

// Pop char element from the char stack
CharStackErrorCode popChar(CharStack** const head);

// Clear char stack
CharStackErrorCode clearCharStack(CharStack** const head);

// Return top element of the char stack
char topChar(CharStack* const head, CharStackErrorCode* const errorCode);