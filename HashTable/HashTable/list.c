#include <string.h>
#include <stdio.h>

#include "List.h"

typedef struct Node
{
    char* value;
    size_t amountOfValue;
    struct Node* next;
} Node;

struct List
{
    Node* head;
    size_t length;
};

List* createList(void)
{
    List* newList = (List*)calloc(1, sizeof(List));
    return newList;
}

bool listIsEmpty(List* list)
{
    return list->head == NULL;
}

ListError addValueToList(List* const list, const char* const value, const size_t amountOfValue)
{
    Node* current = list->head;
    Node* previous = NULL;
    while (current != NULL && strcmp(current->value, value) != 0)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        ++list->length;
        current = (Node*)calloc(1, sizeof(Node));
        if (current == NULL)
        {
            return outOfMemory;
        }

        current->value = _strdup(value);
        if (current->value == NULL)
        {
            free(current);
            return outOfMemory;
        }
        current->amountOfValue = 0;

        if (previous == NULL)
        {
            list->head = current;
        }
        else
        {
            previous->next = current;
        }
    }
    current->amountOfValue += amountOfValue;

    return current->amountOfValue == 1 ? uniqueValue: notUniqueValue;
}

bool listContains(List* const list, const char* const value)
{
    if (list == NULL || value == NULL)
    {
        return false;
    }

    Node* current = list->head;
    while (current != NULL && strcmp(current->value, value) != 0)
    {
        current = current->next;
    }
    return current != NULL;
}

size_t getLength(const List* const list)
{
    return list->length;
}

size_t getAmountOfValue(const List* const list)
{
    return list->head->amountOfValue;
}

const char* getHeadValue(const List* const list)
{
    return (listIsEmpty(list)) ? NULL : list->head->value;
}

void deleteHeadValue(List* const list)
{
    if (list->head == NULL)
    {
        return;
    }
    --list->length;
    Node* trash = list->head;
    list->head = list->head->next;
    free(trash->value);
    free(trash);
}

void deleteList(List** list)
{
    if (*list == NULL)
    {
        return;
    }
    while (!listIsEmpty(*list))
    {
        deleteHeadValue(*list);
    }
    free(*list);
    *list = NULL;
}

void printList(const List* const list)
{
    Node* current = list->head;
    while (current != NULL)
    {
        printf("%s: %Iu\n", current->value, current->amountOfValue);
        current = current->next;
    }
}
