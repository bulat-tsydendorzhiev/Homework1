#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sortedListTests.h"
#include "sortedList.h"

void printComands(void)
{
	printf("Choose one of options:\n");
	printf("0 - exit\n");
	printf("1 - add value to list\n");
	printf("2 - delete value from list\n");
	printf("3 - print list\n");
	printf("Enter your choice: ");
}

int main(void)
{
	const TestErrorCode testErrorCode = tests();
	if (testErrorCode)
	{
		return testErrorCode;
	}

	Node* list = NULL;

	while (true)
	{
		int number = 0;
		int choice = 0;
		printComands();
		scanf_s("%d", &choice);
		printf(choice != 0 ? "---------------------\n" : "");

		switch (choice)
		{
		case 0:
			clearList(&list);
			return 0;
		case 1:
			printf("Enter adding value: ");
			scanf_s("%d", &number);
			pushValue(&list, number);
			printf("\n");
			break;
		case 2:
			printf("Enter deleting value: ");
			scanf_s("%d", &number);
			const ErrorCode errorCode = deleteValue(&list, number);
			printf(errorCode == listIsEmpty ? "List is empty, you can't delete value from empty list\n" : errorCode == deletingANonExistentElement ? "Sorry, but there is no such value in the list\n" : "Deleting was succesfull\n");
			printf("\n");
			break;
		case 3:
			printf("Sorted list: ");
			printList(list);
			printf("\n");
			break;
		default:
			printf("Incorrect input\n");
			printf("Try again\n");
			printf("\n");
			break;
		}

	}
}