#include <stdio.h>

#include "mergeSortTests.h"
#include "list.h"
#include "mergeSort.h"

typedef enum
{
	ok,
	openFileError,
	inputError
} ErrorCode;

int main(void)
{
	const TestErrorCode testErrorCode = tests();
	if (testErrorCode)
	{
		printf("test %d failed\n", testErrorCode);
		return testErrorCode;
	}

	Node* list = NULL;

	ListErrorCode openFileError = loadData(&list, "phoneBook.txt");
	if (openFileError)
	{
		printf("Open file error\n");
		return openFileError;
	}

	printf("Phone book before sorting:\n");
	printList(list);
	printf("\n");

	int choose = 1;
	printf("How should we sort phone book? (by phone = 0, by name = 1): ");
	scanf_s("%d", &choose);
	if (!(choose == 0 || choose == 1))
	{
		printf("Error input\n");
		return inputError;
	}

	mergeSort(&list, choose);

	printf("Sorted phone book by ");
	printf(choose == 1 ? "name:\n" : "phone number:\n");
	printList(list);

	clearList(&list);
	return 0;
}