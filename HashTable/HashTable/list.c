#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "list.h"

typedef struct Node
{
    char* value;
    int frequency;
    struct Node* next;
} Node;

struct List
{
    Node* head;
    int length;
};

List* createList(void)
{
    List* newList = (List*)calloc(1, sizeof(List));
    if (newList == NULL)
    {
        return NULL;
    }
    newList->head = NULL;
    newList->length = 0;
    return newList;
}

bool listIsEmpty(List* list)
{
    return list->head == NULL;
}

int addValueToList(List* const list, const char* const value, const int frequency)
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
            return -1;
        }

        current->value = _strdup(value);
        if (current->value == NULL)
        {
            return -1;
        }
        current->frequency = 0;
        current->next = NULL;

        if (previous == NULL)
        {
            list->head = current;
        }
        else
        {
            previous->next = current;
        }
    }
    current->frequency += frequency;

    return current->frequency == 1;
}

bool listContains(List* const list, const char* const value)
{
    Node* current = list->head;
    while (current != NULL && strcmp(current->value, value) != 0)
    {
        current = current->next;
    }
    return current != NULL;
}

int getLength(List* list)
{
    return list->length;
}

int getFrequency(List* list)
{
    return list->head->frequency;
}

char* getHeadValue(List* const list)
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

void printList(List* list)
{
    Node* current = list->head;
    while (current != NULL)
    {
        printf("%s: %d\n", current->value, current->frequency);
        current = current->next;
    }
}
