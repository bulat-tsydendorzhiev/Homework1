#include <stdlib.h>

#include "StackTests.h"
#include "IntStack.h"
#include "CharStack.h"

static bool runIntStackTests(void)
{
    IntStack* intStack = NULL;
    IntStackErrorCode errorCode = okIntStack;
    
    // Test 1: push element to the int stack
    pushInt(&intStack, 123);
    if (topInt(intStack, &errorCode) != 123)
    {
        clearCharStack(&intStack);
        return false;
    }
    
    // Test 2: pop element from the int stack
    popInt(&intStack);
    if (!intStackIsEmpty(intStack))
    {
        clearCharStack(&intStack);
        return false;
    }
    
    // Test 3: clearing int stack
    pushInt(&intStack, 1);
    pushInt(&intStack, 2);
    pushInt(&intStack, 3);
    pushInt(&intStack, 4);
    
    clearIntStack(&intStack);
    if (!intStackIsEmpty(intStack))
    {
        return false;
    }
    
    return true;
}

static bool runCharStackTests(void)
{
    CharStack* charStack = NULL;
    CharStackErrorCode errorCode = okCharStack;
    
    // Test 1: push element to the int stack
    pushInt(&charStack, '+');
    if (topChar(charStack, &errorCode) != '+')
    {
        clearCharStack(&charStack);
        return false;
    }
    
    // Test 2: pop element from the char stack
    popChar(&charStack);
    if (!charStackIsEmpty(charStack))
    {
        clearCharStack(&charStack);
        return false;
    }
    
    // Test 3: clearing char stack
    pushChar(&charStack, '1');
    pushChar(&charStack, '2');
    pushChar(&charStack, '3');
    pushChar(&charStack, '4');
    
    clearCharStack(&charStack);
    if (!charStackIsEmpty(charStack))
    {
        return false;
    }
    
    return true;
}

bool runTests(void)
{
    return runCharStackTests() && runIntStackTests();
}