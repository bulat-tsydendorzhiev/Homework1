#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "circularList.h"

typedef struct Node
{
    int value;
    struct Node* next;
} Node;

struct CircularList
{
    Node* head;
    Node* tail;
};

CircularList* createCircularList(void)
{
    return (CircularList*)calloc(1, sizeof(CircularList));
}

bool circularListIsEmpty(CircularList* circularList)
{
    return circularList == NULL || circularList->head == NULL;
}

bool append(CircularList* circularList, int value)
{
    Node* temp = (Node*)calloc(1, sizeof(Node));
    if (temp == NULL)
    {
        return false;
    }
    temp->value = value;

    if (circularListIsEmpty(circularList))
    {
        circularList->head = temp;
        circularList->tail = temp;
        temp->next = temp;
    }
    else
    {
        circularList->tail->next = temp;
        temp->next = circularList->head;
        circularList->tail = temp;
    }
    return true;
}

void deletePosition(CircularList* circularList, const int positionNumber)
{
    Node* current = circularList->head;
    Node* previous = circularList->tail;
    for (size_t i = 0; i < positionNumber - 1; ++i)
    {
        previous = current;
        current = current->next;
    }
    circularList->head = current->next;
    circularList->tail = previous;
    previous->next = current->next;
    free(current);
}

bool isOnlyOneLeft(const CircularList*const circularList)
{
    return circularList->head == circularList->tail;
}

int getHeadValue(const CircularList*const circularList)
{
    return circularList->head->value;
}

void clearCircularList(CircularList** const circularList)
{
    Node* current = (*circularList)->head;
    while (current != NULL)
    {
        Node* next = current->next;
        free(current);
        current = next;

        if (current == (*circularList)->head)
            break;
    }
    free(*circularList);
    *circularList = NULL;
}
