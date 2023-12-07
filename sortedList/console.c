#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "console.h"
#include "sortedList.h"

static void printCommands(void)
{
	printf("Choose one of options:\n");
	printf("0 - exit\n");
	printf("1 - add value to sorted list\n");
	printf("2 - delete value from sorted list\n");
	printf("3 - print sorted list\n");
	printf("Enter your choice: ");
}

ConsoleErrorCodes runProgram(void)
{
	SortedList* sortedList = createSortedList();
	if (sortedList == NULL)
	{
		return listError;
	}

	bool exit = false;
	while (!exit)
	{
		int number = 0;
		int choice = 0;
		SortedListErrorCode error = 0;

		printCommands();
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 0:
			exit = true;
			break;
		case 1:
			printf("Adding number: ");
			scanf_s("%d", &number);
			error = addValue(sortedList, number);
			if (error)
			{
				deleteSortedList(&sortedList);
				return listError;
			}
			printf("Successfull adding\n");
			break;
		case 2:
			printf("Deleting number: ");
			scanf_s("%d", &number);
			error = deleteValue(sortedList, number);
			printf(error == deletingNonExistentElement ? "There is no such value in the sorted list\n" : "Successfull deleting\n");
			break;
		case 3:
			printf("Sorted list: ");
			printSortedList(sortedList);
			break;
		default:
			printf("Unknown command. Try again.\n");
			break;
		}
		printf("\n");
	}
	deleteSortedList(&sortedList);
	return success;
}