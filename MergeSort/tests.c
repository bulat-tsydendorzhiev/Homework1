#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "mergeSort.h"
#include "dataInit.h"

static List* initTestList(const char* const fileName)
{
    List* list = createList();
    if (list == NULL)
    {
        return NULL;
    }

    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        deleteList(&list);
        return NULL;
    }

    const DataInitErrorCode errorInitialization = dataInit(file, list);
    if (errorInitialization)
    {
        fclose(file);
        deleteList(&list);
        return NULL;
    }

    fclose(file);
    return list;
}

static bool runSortingByNameTest(void)
{
    List* list = initTestList("sortByNameFile.txt");
    if (list == NULL)
    {
        return false;
    }

    const bool listIsSorted = mergeSort(list, 0);
    if (!listIsSorted)
    {
        deleteList(&list);
        return false;
    }
    return isSorted(list, 0);
}

static bool runSortingByPhoneNumberTest(void)
{
    List* list = initTestList("sortByPhoneNumberFile.txt");
    if (list == NULL)
    {
        return false;
    }

    const bool listIsSorted = mergeSort(list, 1);
    if (!listIsSorted)
    {
        deleteList(&list);
        return false;
    }
    return isSorted(list, 1);
}

bool runTests(void)
{
    if (!runSortingByNameTest())
    {
        printf("Test on sorting phonebook by name failed\n");
        return false;
    }
    if (!runSortingByPhoneNumberTest())
    {
        printf("Test on sorting phonebook by phone number failed\n");
        return false;
    }
    return true;
}