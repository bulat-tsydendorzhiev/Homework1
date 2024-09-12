#pragma once

#include <stdbool.h>

typedef enum
{
    ok,
    emptyQueue,
    outOfMemory
} QueueError;

// Queue
typedef struct Queue Queue;

// Create queue
Queue* createQueue(void);

// Check queue is empty or not
bool queueIsEmpty(const Queue* const queue);

// Push element in queue
int push(Queue* const queue, const int value);

// Return and pop top element in queue
int pop(Queue* const queue);

// Delete queue;
void deleteQueue(Queue** const queue);
