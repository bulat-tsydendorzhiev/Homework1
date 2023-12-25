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
};

SortedList* createSortedList(void)
{
    return (SortedList*)calloc(1, sizeof(SortedList));
}

bool sortedListIsEmpty(const SortedList* const sortedList)
{
    return sortedList->head == NULL;
}

SortedListErrorCode addValue(SortedList* const sortedList, const int value)
{
    Node* current = sortedList->head;
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
        sortedList->head = newNode;
    }
    else
    {
        previous->next = newNode;
    }

    return ok;
}

SortedListErrorCode deleteValue(SortedList* const sortedList, const int value)
{
    Node* current = sortedList->head;
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
        sortedList->head = next;
    }
    else
    {
        previous->next = next;
    }
    
    return ok;
}

void printSortedList(const SortedList* const sortedList)
{
    Node* current = sortedList->head;
    while (current != NULL)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void deleteSortedList(SortedList** sortedList)
{
    while (!sortedListIsEmpty(*sortedList))
    {
        deleteValue(*sortedList, (*sortedList)->head->value);
    }
    free(*sortedList);
    *sortedList = NULL;
}

bool isSorted(const SortedList* const list)
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

void printCommands(void)
{
    printf("Choose one of options:\n");
    printf("0 - exit\n");
    printf("1 - add value to sorted list\n");
    printf("2 - delete value from sorted list\n");
    printf("3 - print sorted list\n");
    printf("Enter your choice: ");
}