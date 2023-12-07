#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sortedList.h"

typedef struct Node
{
    int value;
    struct Node* next;
} Node;

struct SortedList
{
    Node* head;
    Node* tail;
};

SortedList* createSortedList(void)
{
    return (SortedList*)calloc(1, sizeof(SortedList));
}

bool sortedListIsEmpty(const SortedList* const SortedList)
{
    return SortedList->head == NULL;
}

SortedListErrorCode addValue(SortedList* const SortedList, const int value)
{
    Node* current = SortedList->head;
    Node* previous = NULL;
    while (current != NULL && current->value < value)
    {
        previous = current;
        current = current->next;
    }

    Node* newNode = (Node*)calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return outOfMemory;
    }
    newNode->value = value;
    newNode->next = current;

    if (previous == NULL)
    {
        SortedList->head = newNode;
    }
    else
    {
        previous->next = newNode;
    }

    if (newNode->next == NULL)
    {
        SortedList->tail = newNode;
    }

    return ok;
}

SortedListErrorCode deleteValue(SortedList* const SortedList, const int value)
{
    Node* current = SortedList->head;
    Node* previous = NULL;
    while (current != NULL && current->value != value)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        return deletingNonExistentElement;
    }

    Node* next = current->next;
    if (previous == NULL)
    {
        SortedList->head = next;
    }
    else
    {
        previous->next = next;
    }

    if (next == NULL)
    {
        SortedList->tail = NULL;
    }

    return ok;
}

void printSortedList(const SortedList* const SortedList)
{
    Node* current = SortedList->head;
    while (current != NULL)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void deleteSortedList(SortedList** SortedList)
{
    while (!sortedListIsEmpty(*SortedList))
    {
        deleteValue(*SortedList, (*SortedList)->head->value);
    }
    free(*SortedList);
    *SortedList = NULL;
}

bool isSorted(SortedList* list)
{
    if (sortedListIsEmpty(list))
    {
        return true;
    }

    Node* current = list->head;
    while (current->next != NULL)
    {
        if (current->value > current->next->value)
        {
            return false;
        }
        current = current->next;
    }
    return true;
}