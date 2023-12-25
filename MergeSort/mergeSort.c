#include <stdlib.h>
#include <string.h>

#include "mergeSort.h"

static bool split(List* list, List** const leftPart, List** const rightPart)
{
    *leftPart = createList();
    *rightPart = createList();
    if (*leftPart == NULL || *rightPart == NULL)
    {
        return false;
    }

    const size_t length = getListLength(list);
    for (size_t i = 0; i < length; i++)
    {
        if (i < length / 2)
        {
            moveListElementToOtherList(list, *leftPart);
        }
        else
        {
            moveListElementToOtherList(list, *rightPart);
        }
    }
    return true;
}

static void merge(List* list, List* leftPart, List* rightPart, const int key)
{
    while (!listIsEmpty(leftPart) && !listIsEmpty(rightPart))
    {
        if (strcmp(getPartOfContact(leftPart, key), getPartOfContact(rightPart, key)) < 0)
        {
            moveListElementToOtherList(leftPart, list);
        }
        else
        {
            moveListElementToOtherList(rightPart, list);
        }
    }

    while (!listIsEmpty(leftPart))
    {
        moveListElementToOtherList(leftPart, list);
    }

    while (!listIsEmpty(rightPart))
    {
        moveListElementToOtherList(rightPart, list);
    }
}

static bool deleteLists(List** leftPart, List** rightPart)
{
    deleteList(leftPart);
    deleteList(rightPart);
    return listIsEmpty(*leftPart) && listIsEmpty(*rightPart);
}

bool mergeSort(List* list, const int key)
{
    if (getListLength(list) < 2)
    {
        return true;
    }

    List* leftPart = NULL;
    List* rightPart = NULL;
    const bool successfulSplit = split(list, &leftPart, &rightPart);
    if (!successfulSplit)
    {
        deleteLists(&leftPart, &rightPart);
        return false;
    }

    const bool successfullyMergedLeftPart = mergeSort(leftPart, key);
    if (!successfullyMergedLeftPart)
    {
        deleteLists(&leftPart, &rightPart);
        return false;
    }
    const bool successfullyMergedRightPart = mergeSort(rightPart, key);
    if (!successfullyMergedRightPart)
    {
        deleteLists(&leftPart, &rightPart);
        return false;
    }

    merge(list, leftPart, rightPart, key);
    return deleteLists(&leftPart, &rightPart);
}