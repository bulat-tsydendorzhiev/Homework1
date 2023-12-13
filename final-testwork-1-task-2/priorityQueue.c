#include <stdlib.h>

#include "priorityQueue.h"

typedef struct PriorityQueueElement
{
    size_t priority;
    int value;
    struct PriorityQueueElement* next;
} PriorityQueueElement;

struct PriorityQueue
{
    PriorityQueueElement* front;
    PriorityQueueElement* back;
};

static bool priorityQueueIsEmpty(PriorityQueue* const queue)
{
    return queue->front == NULL;
}

PriorityQueue* createPriorityQueue(void)
{
    return (PriorityQueue*)calloc(1, sizeof(PriorityQueue));
}

PriorityQueueError enqueque(PriorityQueue* const queue, const int value, const size_t priority)
{
    PriorityQueueElement* previous = NULL;
    PriorityQueueElement* current = queue->front;
    while (current != NULL && current->priority >= priority)
    {
        previous = current;
        current = current->next;
    }

    PriorityQueueElement* newElement = (PriorityQueueElement*)calloc(1, sizeof(PriorityQueueElement));
    if (newElement == NULL)
    {
        return outOfMemory;
    }
    newElement->priority = priority;
    newElement->value = value;
    newElement->next = current;

    if (previous == NULL)
    {
        queue->front = newElement;
    }
    else
    {
        previous->next = newElement;
    }

    if (newElement->next == NULL)
    {
        queue->back = newElement;
    }

    return success;
}

int dequeque(PriorityQueue* const queue)
{
    if (priorityQueueIsEmpty(queue))
    {
        return -1;
    }

    const int value = queue->front->value;
    PriorityQueueElement* deletingElement = queue->front;
    queue->front = queue->front->next;
    free(deletingElement);
    return value;
}

void deletePriorityQueue(PriorityQueue** const queue)
{
    while (!priorityQueueIsEmpty(*queue))
    {
        dequeque(*queue);
    }
    free(*queue);
    *queue = NULL;
}
