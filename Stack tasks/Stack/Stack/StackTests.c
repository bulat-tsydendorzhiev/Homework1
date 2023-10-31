#include <stdlib.h>

#include "StackTests.h"
#include "IntStack.h"
#include "CharStack.h"

TestErrorCode intStackTests(void)
{
	IntStack* intStack = NULL;
	IntErrorCode errorCode = okIntStack;

	// Test 1: push element to the int stack
	pushInt(&intStack, 123);
	if (topInt(intStack, &errorCode) != 123)
	{
		return test1Failed;
	}

	// Test 2: pop element from the int stack
	popInt(&intStack);
	if (!intStackIsEmpty(intStack))
	{
		return test2Failed;
	}

	// Test 3: clearing char stack
	pushInt(&intStack, 1);
	pushInt(&intStack, 2);
	pushInt(&intStack, 3);
	pushInt(&intStack, 4);

	clearIntStack(&intStack);
	if (!intStackIsEmpty(intStack))
	{
		return test3Failed;
	}

	return testsPassed;
}

TestErrorCode charStackTests(void)
{
	CharStack* charStack = NULL;
	CharErrorCode errorCode = okCharStack;

	// Test 1: push element to the int stack
	pushInt(&charStack, '+');
	if (topChar(charStack, &errorCode) != '+')
	{
		return test1Failed;
	}

	// Test 2: pop element from the char stack
	popChar(&charStack);
	if (!charStackIsEmpty(charStack))
	{
		return test2Failed;
	}

	// Test 3: clearing char stack
	pushChar(&charStack, '1');
	pushChar(&charStack, '2');
	pushChar(&charStack, '3');
	pushChar(&charStack, '4');

	clearCharStack(&charStack);
	if (!charStackIsEmpty(charStack))
	{
		return test3Failed;
	}

	return testsPassed;
}
