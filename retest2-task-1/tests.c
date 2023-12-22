#include <stdlib.h>
#include <stdio.h>

#include "tests.h"
#include "readAndWriteData.h"
#include "queue.h"

static bool checkOutput(const int* const expected, const size_t length)
{
    FILE* file = NULL;
    fopen_s(&file, "output.txt", "r");
    if (file == NULL)
    {
        return false;
    }

    Queue* queue = createQueue();
    if (queue == NULL)
    {
        fclose(file);
        return false;
    }

    while (!feof(file))
    {
        int number = 0;
        fscanf_s(file, "%d", &number);
        const int errorPush = push(queue, number);
        if (errorPush)
        {
            deleteQueue(&queue);
        }
    }

    for (size_t i = 0; i < length; i++)
    {
        const int value = pop(queue);
        if (value != expected[i])
        {
            deleteQueue(&queue);
            return false;
        }
    }

    return !queueIsEmpty(queue);
}

static int testFunction(const char* testFileName, const int lessNumber, const int greaterNumber)
{
    Queue* lessQueue = createQueue();
    Queue* middleQueue = createQueue();
    Queue* greaterQueue = createQueue();
    if (lessQueue == NULL || middleQueue == NULL || greaterQueue == NULL)
    {
        return 2;
    }

    const int errorLoad = getDataFromFile(testFileName, lessQueue, middleQueue, greaterQueue, lessNumber, greaterNumber);
    if (errorLoad)
    {
        deleteQueue(&lessQueue);
        deleteQueue(&middleQueue);
        deleteQueue(&greaterQueue);
        return errorLoad;
    }

    const int writtingError = writeNumbersToFile("output.txt", lessQueue, middleQueue, greaterQueue);
    if (writtingError)
    {
        deleteQueue(&lessQueue);
        deleteQueue(&middleQueue);
        deleteQueue(&greaterQueue);
        return writtingError;
    }

    deleteQueue(&lessQueue);
    deleteQueue(&middleQueue);
    deleteQueue(&greaterQueue);
    return 0;
}

bool runTests(void)
{
    const char testFileNames[][10] = { "test1.txt" };
    const int testValues[][2] = { {3, 6} };
    const int expected[][10] = { {1, 2, 3, 4, 5, 6, 7, 8, 9, 10} };
    const size_t lengths[] = {10, };
    for (size_t i = 0; i < 1; i++)
    {
        const int error = testFunction(testFileNames[i], testValues[i][0], testValues[i][0]);
        if (error)
        {
            return false;
        }

        const bool testFailed = checkOutput(expected[i], lengths[i]);
        if (testFailed)
        {
            return false;
        }
    }
    return true;
}