#pragma once

#include <stdbool.h>

// success: everything is alright;
// outOfMemory: lack of memory became;
typedef enum
{
    success,
    outOfMemory = 2
} PriorityQueueError;

// Priority queue
typedef struct PriorityQueue PriorityQueue;

// return pointer to Priority queue
PriorityQueue* createPriorityQueue(void);

// push the element in accordance with its priority
PriorityQueueError enqueque(PriorityQueue* queue, const int value, const size_t priority);

// return front value and delete it; if queue is empty return -1
int dequeque(PriorityQueue* queue);

// Delete priority queue
void deletePriorityQueue(PriorityQueue** queue);
