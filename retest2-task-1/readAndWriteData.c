#include <stdio.h>

#include "readAndWriteData.h"

int getDataFromFile(const char* const fileName, Queue* const lessQueue, Queue* const middleQueue, Queue* const greaterQueue,
    const int lessNumber, const int greaterNumber)
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        return errorOpening;
    }

    size_t numberOfValues = 0;
    fscanf_s(file, "%Iu", &numberOfValues);

    for (size_t i = 0; i < numberOfValues; ++i)
    {
        int number = 0;
        fscanf_s(file, "%d", &number);
        if (number < lessNumber)
        {
            const int error = push(lessQueue, number);
            if (error)
            {
                fclose(file);
                return error;
            }
        }
        else if (number >= lessNumber && number <= greaterNumber)
        {
            const int error = push(middleQueue, number);
            if (error)
            {
                fclose(file);
                return error;
            }
        }
        else
        {
            const int error = push(greaterQueue, number);
            if (error)
            {
                fclose(file);
                return error;
            }
        }
    }

    fclose(file);
    return success;
}

int writeNumbersToFile(const char* const fileName, Queue* const lessQueue, Queue* const middleQueue, Queue* const greaterQueue)
{
    FILE* outputFile = NULL;
    fopen_s(&outputFile, fileName, "w");
    if (outputFile == NULL)
    {
        return errorOpening;
    }

    while (!queueIsEmpty(lessQueue))
    {
        const int value = pop(lessQueue);
        fprintf(outputFile, "%d ", value);
    }
    while (!queueIsEmpty(middleQueue))
    {
        const int value = pop(middleQueue);
        fprintf(outputFile, "%d ", value);
    }
    while (!queueIsEmpty(greaterQueue))
    {
        const int value = pop(greaterQueue);
        fprintf(outputFile, "%d ", value);
    }

    return 0;
}
