#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUMBER_OF_TESTS 4

typedef enum
{
    testsFailed = -1,
    success,
    incorrectInput,
    outOfMemory
} ErrorCode;

ErrorCode readAndCheckData(size_t* const arrayLength)
{
    printf("Input array length: ");
    int scanResult = scanf_s("%Iu", arrayLength);
    while (scanResult == 0)
    {
        scanf_s("%*[^\n]");
        printf("Invalid input! Please, enter the number: ");
        scanResult = scanf_s("%Iu", arrayLength);
    }
    if (*arrayLength < 0)
    {
        return incorrectInput;
    }
    return success;
}

void createArrayOfRandomNumbers(int* array, const size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        array[i] = rand() % 1000;
    }
}

void printArray(int* array, const size_t arrayLength)
{
    for (size_t i = 0; i < arrayLength; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void swap(int* number1, int* number2)
{
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

void halfQsort(int* array, const size_t length)
{
    const int pivot = array[0];
    size_t smaller = 0;

    for (size_t i = 1; i < length; ++i)
    {
        if (array[i] < pivot)
        {
            ++smaller;
            swap(&array[i], &array[smaller]);
        }
    }
    swap(&array[0], &array[smaller]);
}

bool isCorrectArray(const int* const array, const size_t arrayLength, const int pivot)
{
    bool shouldBeLess = true;
    for (size_t i = 0; i < arrayLength; i++)
    {
        if (array[i] == pivot)
        {
            shouldBeLess = false;
        }
        else if ((array[i] < pivot) != shouldBeLess)
        {
            return false;
        }
    }
    return true;
}

void runTests(bool* testResults)
{
    int testArray1[] = { 3, 1, 4, 1, 5, 9 };
    halfQsort(testArray1, 6);
    testResults[0] = isCorrectArray(testArray1, 6, 3);

    int testArray2[] = { 5, 4, 3, 2, 1 };
    halfQsort(testArray2, 5);
    testResults[1] = isCorrectArray(testArray2, 5, 5);

    int testArray3[] = { 1, 2, 3, 4, 5 };
    halfQsort(testArray3, 5);
    testResults[2] = isCorrectArray(testArray3, 5, 1);

    int testArray4[] = { 1 };
    halfQsort(testArray4, 1);
    testResults[3] = isCorrectArray(testArray4, 1, 1);
}

int main()
{
    bool testResults[NUMBER_OF_TESTS] = { false };
    bool testsPassed = true;
    runTests(testResults);
    for (size_t i = 0; i < NUMBER_OF_TESTS; ++i)
    {
        if (!testResults[i])
        {
            printf("Test %Iu failed\n", i + 1);
            testsPassed = false;
        }
    }

    if (!testsPassed)
    {
        return testsFailed;
    }

    size_t arrayLength = 0;
    printf("Enter number (less than 100): ");
    const ErrorCode errorInput = readAndCheckData(&arrayLength);
    if (errorInput)
    {
        printf("Array length cannot be negative number\n");
        return errorInput;
    }
    
    int* array = (int*)calloc(arrayLength, sizeof(int));
    if (array == NULL)
    {
        printf("Out of memory error\n");
        return outOfMemory;
    }

    createArrayOfRandomNumbers(array, arrayLength);
    printf("Array before: ");
    printArray(array, arrayLength);

    halfQsort(array, arrayLength);
    printf("Array after: ");
    printArray(array, arrayLength);

    free(array);
    return success;
}