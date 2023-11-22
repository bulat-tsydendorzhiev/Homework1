#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "list.h"

typedef struct Node
{
    int value;
    int index;
    struct Node* next;
} Node;

struct List
{
    Node* head;
    Node* tail;
    int length;
};

List* createList(void)
{
    return (List*)calloc(1, sizeof(List));
}

bool listIsEmpty(List* list)
{
    return list->head == NULL;
}

Node* createNode(const int value, const int index)
{
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return NULL;
    }
    newNode->value = value;
    newNode->index = index;
    newNode->next = NULL;

    return newNode;
}

ListErrorCode add(List* const list, const int value)
{
    const int index = listIsEmpty(list) ? 0 : list->tail->index + 1;
    Node* newNode = createNode(value, index);
    if (newNode == NULL)
    {
        return outOfMemotyList;
    }

    if (listIsEmpty(list))
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        list->tail = list->tail->next;
    }
    ++list->length;
    return okList;
}

bool contains(List* list, const int value)
{
    Node* current = list->head;
    while (current != list->tail)
    {
        if (current->value == value)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool isEndOfList(List* list)
{
    return list->head == list->tail;
}

int getLength(List* list)
{
    return list->length;
}

void deleteListElement(List* list, const int index)
{
    Node* previous = NULL;
    Node* current = list->head;
    while (current != list->tail && current->index != index)
    {
        previous = current;
        current = current->next;
    }

    if (previous == NULL)
    {
        return;
    }

    previous->next = current->next;
    free(current);
}

static void deleteNodes(Node** head)
{
    if ((*head) == NULL)
    {
        return;
    }

    while ((*head) != NULL)
    {
        Node* trash = *head;
        (*head) = (*head)->next;
        free(trash);
    }
    *head = NULL;
}

void deleteList(List** list)
{
    deleteNodes(&(*list)->head);
    free(*list);
    *list = NULL;
}

void printList(List* list)
{
    Node* current = list->head;
    while (current != NULL)
    {
        printf("%d ", current->value);
        current = current->next;
    }
}
