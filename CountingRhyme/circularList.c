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

CircularListError createCircularList(CircularList** circularList)
{
    *circularList = malloc(sizeof(circularList));
    if (*circularList == NULL)
    {
        return circularListIsEmptyError;
    }
    (*circularList)->head = NULL;
    (*circularList)->tail = NULL;
    return okCircularList;
}

CircularListError append(CircularList** circularList, int value)
{
    Node* temp = malloc(sizeof(Node));
    if (temp == NULL)
    {
        return circularListOutOfMemory;
    }
    temp->value = value;
    temp->next = NULL;

    if (circularListisEmpty(*circularList))
    {
        (*circularList)->head = temp;
        (*circularList)->tail = temp;
        temp->next = temp;
        return okCircularList;
    }

    (*circularList)->tail->next = temp;
    temp->next = (*circularList)->head;
    (*circularList)->tail = temp;
    return okCircularList;
}

bool circularListisEmpty(CircularList* circularList)
{
    return circularList->head == NULL;
}

CircularListError deletePosition(CircularList** circularList, const int positionNumber)
{
    Node* current = (*circularList)->head;
    Node* previous = (*circularList)->tail;
    for (int i = 1; i < positionNumber; ++i)
    {
        previous = current;
        current = current->next;
    }

    (*circularList)->head = current->next;
    (*circularList)->tail = previous;
    previous->next = current->next;
    free(current);
    return okCircularList;
}

bool onlyOneLeft(CircularList* circularList)
{
    return circularList->head == circularList->tail;
}

int getHeadValue(CircularList* circularList)
{
    return circularList->head->value;
}

void clearCircularList(CircularList** circularList)
{
    Node* current = (*circularList)->head;

    while (circularListisEmpty(*circularList)) {
        Node* next = current->next;
        free(current);
        current = next;

        if (current == (*circularList)->head)
            break;
    }

    (*circularList)->head = NULL;
    (*circularList)->tail = NULL;
}
