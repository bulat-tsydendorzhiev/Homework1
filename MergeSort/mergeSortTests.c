#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "mergeSortTests.h"
#include "list.h"
#include "mergeSort.h"

bool isSimilar(Node* list, Node* expectedList, int gettingField)
{
	while (list != NULL)
	{
		if (strcmp(getField(list, gettingField), getField(expectedList, gettingField)) != 0 || strcmp(getField(list, !gettingField), getField(expectedList, !gettingField)) != 0)
		{
			return false;
		}
		ListErrorCode listErrorCode = okList;
		list = getNextNode(list, &listErrorCode);
		expectedList = getNextNode(expectedList, &listErrorCode);
	}
	return true;
}

TestErrorCode tests(void)
{
	// Test 1: sorting list by phone
	Node* testList1 = NULL;
	Node* expectedList11 = NULL;
	append(&expectedList11, "John", "123456789");
	append(&expectedList11, "Bob", "456789123");
	append(&expectedList11, "Alice", "987654321");

	loadData(&testList1, "sortingTest1-2.txt");
	mergeSort(&testList1, 0);
	if (!isSimilar(testList1, expectedList11, 0))
	{
		return testErrorCode1;
	}
	clearList(&expectedList11);

	// Test 2: sorting list by name
	Node* expectedList12 = NULL;
	append(&expectedList12, "Alice", "987654321");
	append(&expectedList12, "Bob", "456789123");
	append(&expectedList12, "John", "123456789");

	mergeSort(&testList1, 1);
	if (!isSimilar(testList1, expectedList12, 1))
	{
		return testErrorCode2;
	}
	clearList(&testList1);
	clearList(&expectedList12);

	// Test 3: sorting list with the same names
	Node* testList2 = NULL;
	Node* expectedList2 = NULL;
	append(&expectedList2, "John", "123456789");
	append(&expectedList2, "John", "456789123");
	append(&expectedList2, "John", "987654321");

	loadData(&testList2, "sortingTest3.txt");
	mergeSort(&testList2, 1);
	if (!isSimilar(testList2, expectedList2, 1))
	{
		return testErrorCode3;
	}
	clearList(&testList2);
	clearList(&expectedList2);

	// Test 4: sorting list with the same phone numbers
	Node* testList3 = NULL;
	Node* expectedList3 = NULL;
	append(&expectedList3, "John", "123456789");
	append(&expectedList3, "Alice", "123456789");
	append(&expectedList3, "Bob", "123456789");

	loadData(&testList3, "sortingTest4.txt");
	mergeSort(&testList3, 0);
	if (!isSimilar(testList3, expectedList3, 0))
	{
		return testErrorCode4;
	}
	clearList(&testList3);
	clearList(&expectedList3);

	// Test 5: sorting list from file without anything
	Node* testList4 = NULL;

	loadData(&testList4, "sortingTest5.txt");
	mergeSort(&testList4, 0);
	if (testList4 != NULL)
	{
		return testErrorCode5;
	}

	return testsPassed;
}