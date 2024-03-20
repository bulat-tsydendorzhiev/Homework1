#include <stdlib.h>
#include <stdio.h>

#include "console.h"
#include "dataInit.h"
#include "list.h"
#include "mergeSort.h"

ConsoleErrorCode runProgram(void)
{
    List* phoneBook = createList();
    if (phoneBook == NULL)
    {
        return listError;
    }

    FILE* file = NULL;
    fopen_s(&file, "mainFile.txt", "r");
    if (file == NULL)
    {
        deleteList(&phoneBook);
        return fileError;
    }

    const DataInitErrorCode errorLoad = dataInit(file, phoneBook);
    if (errorLoad)
    {
        fclose(file);
        deleteList(&phoneBook);
        return errorLoad;
    }
    fclose(file);

    int key = 0;
    const DataInitErrorCode errorKeyInit = getKey(&key);
    if (errorKeyInit)
    {
        printf("Incorrect input\n");
        deleteList(&phoneBook);
        return errorKeyInit;
    }

    const bool isSortedList = mergeSort(phoneBook, key);
    if (!isSortedList)
    {
        deleteList(&phoneBook);
        return sortingError;
    }

    printf("Sorted phone book:\n");
    printList(phoneBook);

    deleteList(&phoneBook);
    return success;
}