#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum
{
    testsFailed = -1,
    ok,
    scanError,
    outOfMemory
} ErrorCodes;

void swap(int* number1, int* number2)
{
    const int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

void insertionSort(int* array, int left, int right)
{
    for (size_t i = left; i <= right; ++i)
    {
        const int value = array[i];
        int j = i;
        while (j > left && array[j - 1] > value)
        {
            array[j] = array[j - 1];
            --j;
        }
        array[j] = value;
    }
}

void smartQsort(int* const array, const int left, const int right)
{
    if (right - left + 1 <= 10)
    {
        insertionSort(array, left, right);
        return;
    }
    const int pivot = array[(left + right) / 2];
    size_t i = left;
    size_t j = right;

    while (i <= j)
    {
        while (array[i] < pivot)
        {
            i++;
        }
        while (array[j] > pivot)
        {
            j--;
        }

        if (i <= j)
        {
            swap(&array[i], &array[j]);
            ++i;
            --j;
        }
    }

    if (left < j)
    {
        smartQsort(array, left, j + 1);
    }
    if (i < right)
    {
        smartQsort(array, i, right);
    }
}

void printSortedArray(const int* const array, const int arrayLength)
{
    for (size_t i = 0; i < arrayLength; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

bool isSorted(const int* const array, const size_t arrayLength)
{
    if (arrayLength == 1)
    {
        return true;
    }
    for (size_t i = 1; i < arrayLength; ++i)
    {
        if (array[i - 1] > array[i])
        {
            return false;
        }
    }
    return true;
}

bool runTests(void)
{
    int testArrays[][20] = { {1},
                        {5, 4, 3, 2, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                        {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
                        {1, 3, 2, 0, -1, 5, 6, 7, 2, 9, -12, 68, 37, 21, 99, 214, 62, 63, 12, 0} };
    const size_t testArraysLengths[] = { 1, 5, 15, 16, 20 };

    for (size_t i = 0; i < 4; ++i)
    {
        smartQsort(testArrays[i], 0, testArraysLengths[i] - 1);
        if (!isSorted(testArrays[i], testArraysLengths[i]))
        {
            printf("Test %Iu failed\n", i + 1);
            return false;
        }
    }
    return true;
}

int initData(int** const array, int* const arrayLength)
{
    printf("Enter array length: ");
    if (scanf_s("%d", arrayLength) != 1 || *arrayLength <= 0)
    {
        return scanError;
    }

    *array = (int*)calloc(*arrayLength, sizeof(int));
    if (*array == NULL)
    {
        return outOfMemory;
    }

    printf("Enter array elements: ");
    for (size_t i = 0; i < *arrayLength; ++i)
    {
        if (scanf_s("%d", &(*array)[i]) != 1)
        {
            free(*array);
            return scanError;
        }
    }
    return ok;
}

int main(void)
{
    const bool testsPassed = runTests();
    if (!testsPassed)
    {
        return testsFailed;
    }
    
    int arrayLength = 0;
    int* array = NULL;
    const int errorInit = initData(&array, &arrayLength);
    if (errorInit)
    {
        return errorInit;
    }

    smartQsort(array, 0, arrayLength - 1);

    printf("Sorted array: ");
    printSortedArray(array, arrayLength);

    free(array);
    return ok;
}
