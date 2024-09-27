#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "console.h"
#include "sortedList.h"

ConsoleErrorCodes runProgram(void)
{
    SortedList* sortedList = createSortedList();
    if (sortedList == NULL)
    {
        return listError;
    }
    
    while (true)
    {
        int choice = 0;

        printCommands();
        scanf_s("%d", &choice);
        switch (choice)
        {
        case exitCommand:
            deleteSortedList(&sortedList);
            return success;
        case addValueToList:
        {
            int number = 0;
            printf("Enter adding number: ");
            if (scanf_s("%d", &number) != 1)
            {
                deleteSortedList(&sortedList);
                return scanError;
            }
            const SortedListErrorCode addingError = addValue(sortedList, number);
            if (addingError)
            {
                deleteSortedList(&sortedList);
                return listError;
            }
            printf("Successful adding\n");
            break;
        }
        case deleteValueFromList:
        {
            int number = 0;
            printf("Enter deleting number: ");
            if (scanf_s("%d", &number) != 1)
            {
                deleteSortedList(&sortedList);
                return scanError;
            }
            const SortedListErrorCode deletingError = deleteValue(sortedList, number);
            printf(deletingError == deletingNonExistentElement ? "There is no such value in the sorted list\n" : "Successfull deleting\n");
            break;
        }
        case printList:
            printf("Sorted list: ");
            printSortedList(sortedList);
            break;
        default:
            printf("Unknown command. Try again.\n");
            break;
        }
        printf("\n");
    }
}