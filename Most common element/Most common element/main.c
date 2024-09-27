#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TESTS_FAILED -1
#define SUCCESS 0
#define SCAN_ERROR 1
#define OUT_OF_MEMORY 2

void swap(int* number1, int* number2)
{
    const int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

void insertionSort(int* array, const int left, const int right)
{
    int value, j;
    for (int i = left; i <= right; ++i)
    {
        value = array[i];
        j = i;
        while (j > left && array[j - 1] > value)
        {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = value;
    }
}

void quickSort(int* const array, const int left, const int right)
{
    if (right - left + 1 <= 10)
    {
        insertionSort(array, left, right);
        return;
    }
    const int pivot = array[(left + right) / 2];
    int i = left;
    int j = right;

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
            swap(&array[j], &array[i]);
            i++;
            j--;
        }
    }

    if (left < j)
    {
        quickSort(array, left, j + 1);
    }
    if (i < right)
    {
        quickSort(array, i, right);
    }
}

int searchMostFrequent(const int* const array, const int arrayLength)
{
    int answer = array[0];
    int maxCount = 1;
    int count = 1;

    for (size_t i = 1; i < arrayLength; ++i)
    {
        if (array[i - 1] == array[i])
        {
            ++count;
            if (count > maxCount)
            {
                maxCount = count;
                answer = array[i - 1];
            }
        }
        else
        {
            count = 1;
        }
    }
    return answer;
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

bool testsForQuickSort(void)
{
    int testArrays[][20] = { {1},
                        {5, 4, 3, 2, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                        {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
                        {1, 3, 2, 0, -1, 5, 6, 7, 2, 9, -12, 68, 37, 21, 99, 214, 62, 63, 12, 0} };
    const size_t testArraysLengths[] = { 1, 5, 15, 15, 20 };

    for (size_t i = 0; i < 5; ++i)
    {
        quickSort(testArrays[i], 0, testArraysLengths[i] - 1);
        if (!isSorted(testArrays[i], testArraysLengths[i]))
        {
            return false;
        }
    }
    return true;
}

bool testForSearching(void)
{
    const int testArrays[][10] = { {1},
                                {1, 2, 2, 3, 3, 3, 4, 4, 4, 4},
                                {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                                {12, 12, 13, 13, 14, 14} };
    const int testArraysLengths[] = { 1, 10, 10, 6 };
    const int expectedResults[] = { 1, 4, 1, 12 };

    for (size_t i = 0; i < 4; i++)
    {
        const int result = searchMostFrequent(testArrays[i], testArraysLengths[i]);
        if (result != expectedResults[i])
        {
            return false;
        }
    }
    return true;
}

bool tests(void)
{
    if (!testsForQuickSort())
    {
        printf("Tests for quick sort failed\n");
        return false;
    }
    if (!testForSearching())
    {
        printf("Tests for searching failed\n");
        return false;
    }
    return true;
}

int initData(int* const arrayLength, int** const array)
{
    printf("Enter array length: ");
    if (scanf_s("%d", arrayLength) != 1 || *arrayLength <= 0)
    {
        return SCAN_ERROR;
    }

    *array = (int*)calloc(*arrayLength, sizeof(int));
    if (*array == NULL)
    {
        return OUT_OF_MEMORY;
    }

    printf("Enter array: ");
    for (size_t i = 0; i < *arrayLength; i++)
    {
        if (scanf_s("%d", &(*array)[i]) != 1)
        {
            free(*array);
            return SCAN_ERROR;
        }
    }
    return SUCCESS;
}

int main(void)
{
    const bool testPassed = tests();
    if (!testPassed)
    {
        return TESTS_FAILED;
    }

    int* array = NULL;
    int arrayLength = 0;
    const int errorInit = initData(&arrayLength, &array);
    if (errorInit)
    {
        printf("Error during initialization\n");
        return errorInit;
    }

    quickSort(array, 0, arrayLength - 1);
    const int mostFrequentElement = searchMostFrequent(array, arrayLength);
    printf("Most frequent element in array is %d\n", mostFrequentElement);

    free(array);
    return SUCCESS;
}