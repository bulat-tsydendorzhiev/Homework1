#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "list.h"

typedef struct Node
{
    char* name;
    char* phoneNumber;
    struct Node* next;
} Node;

struct List
{
    Node* head;
    Node* tail;
    size_t length;
};

List* createList(void)
{
    return (List*)calloc(1, sizeof(List));
}

bool listIsEmpty(List* list)
{
    return list == NULL || list->head == NULL;
}

size_t getListLength(List* list)
{
    return list->length;
}

char* getPartOfContact(const List* const list, const int key)
{
    if (listIsEmpty(list))
    {
        return NULL;
    }
    return (key == 0) ? list->head->name : list->head->phoneNumber;
}

static void deleteNode(Node** node)
{
    free((*node)->name);
    free((*node)->phoneNumber);
    free(*node);
    *node = NULL;
}

static Node* createNode(const char* name, const char* const phoneNumber)
{
    Node* node = (Node*)calloc(1, sizeof(Node));
    if (node == NULL)
    {
        return NULL;
    }
    node->name = _strdup(name);
    node->phoneNumber = _strdup(phoneNumber);
    if (node->name == NULL || node->phoneNumber == NULL)
    {
        deleteNode(&node);
        return NULL;
    }
    return node;
}

static void insert(List* list, Node* listElement)
{
    listElement->next = NULL;
    if (listIsEmpty(list))
    {
        list->head = listElement;
    }
    else
    {
        list->tail->next = listElement;
    }
    list->tail = listElement;
    ++list->length;
}

static void removeListElement(List* list, Node* listElement)
{
    list->head = listElement->next;
    if (listElement == list->tail)
    {
        list->tail = listElement->next;
    }
    --list->length;
}

bool append(List* list, const char* const name, const char* const phoneNumber)
{
    Node* newContact = createNode(name, phoneNumber);
    if (newContact == NULL)
    {
        return false;
    }

    insert(list, newContact);
    return true;
}

void moveListElementToOtherList(List* listFrom, List* listTo)
{
    if (listIsEmpty(listFrom))
    {
        return;
    }

    Node* movingElement = listFrom->head;
    removeListElement(listFrom, movingElement);
    insert(listTo, movingElement);
}

void printList(List* list)
{
    Node* current = list->head;
    while (current != NULL)
    {
        printf("%s - %s\n", current->name, current->phoneNumber);
        current = current->next;
    }
}

static void deleteHeadValue(List* list)
{
    if (listIsEmpty(list))
    {
        return;
    }
    Node* removingNode = list->head;
    removeListElement(list, removingNode);
    deleteNode(&removingNode);
}

void deleteList(List** list)
{
    while (!listIsEmpty(*list))
    {
        deleteHeadValue(*list);
    }
    free(*list);
    *list = NULL;
}

static bool compare(const Node* const current, const Node* const next, const int key)
{
    return (key == 0) ? strcmp(current->name, next->name) < 0 : strcmp(current->phoneNumber, next->phoneNumber) < 0;
}

bool isSorted(const List* const list, const int key)
{
    if (listIsEmpty(list))
    {
        return true;
    }

    Node* current = list->head;
    while (current->next != NULL)
    {
        if (!compare(current, current->next, key))
        {
            return false;
        }
        current = current->next;
    }
    return true;
}
