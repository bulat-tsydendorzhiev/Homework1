#include <stdlib.h>
#include <stdio.h>

#include "sortedListTests.h"
#include "sortedList.h"

TestErrorCode tests(void)
{
	Node* testList = NULL;

	// Test 1: adding value
	const ErrorCode errorCode1 = pushValue(&testList, 123);
	if (errorCode1)
	{
		printf("test %d failed\n", 1);
		return test1Failed;
	}

	// Adding values for next tests
	pushValue(&testList, 123);
	pushValue(&testList, 456);
	pushValue(&testList, 789);
	pushValue(&testList, 0);

	//Test 2: deleting an existing value
	const ErrorCode errorCode2 = deleteValue(&testList, 123);
	if (errorCode2 != ok)
	{
		printf("test %d failed\n", 2);
		return test2Failed;
	}

	//Test 3: deleting a non-existing value
	const ErrorCode errorCode3 = deleteValue(&testList, 1234567890);
	if (errorCode3 != deletingANonExistentElement)
	{
		printf("test %d failed\n", 3);
		return test3Failed;
	}

	//Test 4: clearing filled list
	const ErrorCode errorCode4 = clearList(&testList);
	if (errorCode4 != ok || testList != NULL)
	{
		printf("test %d failed\n", 4);
		return test4Failed;
	}

	//Test 5: clearing empty list
	const ErrorCode errorCode5 = clearList(&testList);
	if (errorCode5 != listIsEmpty || testList != NULL)
	{
		printf("test %d failed\n", 5);
		return test5Failed;
	}

	return testPassed;
}