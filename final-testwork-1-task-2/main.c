#include <stdio.h>
#include <stdbool.h>

#include "priorityQueue.h"

#define OK 0
#define TEST_FAILED -1

bool enqueueTest(PriorityQueue* queue)
{
    const int pushingValues[5][2] = { {1, 5},
                                 {2, 4},
                                 {124513215,4},
                                 {531, 2},
                                 {124, 1} };
    for (size_t i = 0; i < 5; ++i)
    {
        const PriorityQueueError errorEnqueque = enqueque(queue, pushingValues[i][0], pushingValues[i][1]);
        if (errorEnqueque)
        {
            return false;
        }
    }
    return true;
}

bool dequeueTest(PriorityQueue* queue)
{
    const int expected[] = {1, 2, 124513215, 531, 124 };
    for (size_t i = 0; i < 5; i++)
    {
        const int value = dequeque(queue);
        if (value != expected[i])
        {
            return false;
        }
    }
    return dequeque(queue) == -1;
}

bool tests(void)
{
    PriorityQueue* queue = createPriorityQueue();
    if (queue == NULL)
    {
        return false;
    }

    const bool enqueueTestPassed = enqueueTest(queue);
    if (!enqueueTestPassed)
    {
        deletePriorityQueue(&queue);
        return false;
    }

    const bool dequeueTestPassed = dequeueTest(queue);
    if (!enqueueTestPassed)
    {
        deletePriorityQueue(&queue);
        return false;
    }

    deletePriorityQueue(&queue);
    return true;
}

int main()
{
    const bool testPassed = tests();
    if (!testPassed)
    {
        return TEST_FAILED;
    }
    return OK;
}