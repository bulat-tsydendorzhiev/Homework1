#include <stdlib.h>

#include "queue.h"

typedef struct Node
{
    int value;
    struct Node* next;
} Node;

struct Queue
{
    Node* front;
    Node* back;
};

Queue* createQueue(void)
{
    return (Queue*)calloc(1, sizeof(Queue));
}

bool queueIsEmpty(const Queue* const queue)
{
    return queue->front == NULL;
}

int push(Queue* const queue, const int value)
{
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return outOfMemory;
    }
    newNode->value = value;

    if (queueIsEmpty(queue))
    {
        queue->front = newNode;
    }
    else
    {
        queue->back->next = newNode;
    }
    queue->back = newNode;

    return ok;
}

int pop(Queue* const queue)
{
    if (queueIsEmpty(queue))
    {
        return emptyQueue;
    }

    Node* trash = queue->front;
    const int value = queue->front->value;
    queue->front = queue->front->next;
    free(trash);

    return value;
}

void deleteQueue(Queue** const queue)
{
    while (!queueIsEmpty(*queue))
    {
        pop(*queue);
    }
    free(*queue);
    *queue = NULL;
}