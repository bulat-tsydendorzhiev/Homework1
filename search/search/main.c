#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TESTS_FAILED -1
#define SUCCESS 0
#define SCAN_ERROR 1
#define OUT_OF_MEMORY 2
#define RANGE_OF_RANDOM_NUMBERS 1000

void swap(int* number1, int* number2)
{
    const int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

void insertionSort(int* const array, int left, int right)
{
    for (size_t i = left; i <= right; ++i)
    {
        const int value = array[i];
        int j = i;
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

int binarySearch(const int number, const int* const array, const int length)
{
    int start = 0;
    int end = length - 1;

    while (start <= end)
    {
        const int middleIndex = (start + end) / 2;
        if (number == array[middleIndex])
        {
            return middleIndex;
        }
        else if (array[middleIndex] < number)
        {
            start = middleIndex + 1;
        }
        else
        {
            end = middleIndex - 1;
        }
    }
    return -1;
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
                        {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
                        {1, 3, 2, 0, -1, 5, 6, 7, 2, 9, -12, 68, 37, 21, 99, 214, 62, 63, 12, 0} };
    const size_t testArraysLengths[] = { 1, 5, 15, 16, 20 };

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

bool testForBinarySearch(void)
{
    const int testArrays[][20] = { {1},
                                {2, 2, 2, 2, 2},
                                {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                                { -12, -1, 0, 0, 1, 2, 2, 3, 4, 6, 7, 9, 12, 21, 37, 62, 63, 68, 99, 214},
                                {3, 1, 4, 1, 5, 9, 2, 6, 5} };
    const int testArraysLengths[] = {1, 5, 10, 20, 9};
    const int targets[] = {1, 2, 3, 4, 123};
    const int expectedResults[] = { 0, 2, 2, 8, -1};
    for (size_t i = 0; i < 5; i++)
    {
        if (binarySearch(targets[i], testArrays[i], testArraysLengths[i]) != expectedResults[i])
        {
            return false;
        }
    }
    return true;
}

bool tests()
{
    if (!testsForQuickSort())
    {
        printf("Tests for quick sort failed\n");
        return false;
    }
    if (!testForBinarySearch())
    {
        printf("Tests for binary search failed\n");
        return false;
    }
    return true;
}

bool readData(int* const arrayLength, int* const amountOfRandomNumbers)
{
    printf("Enter array length and amount of random numbers: ");
    return scanf_s("%d %d", arrayLength, amountOfRandomNumbers) == 2 && *arrayLength > 0 && *amountOfRandomNumbers > 0;
}

int* createArrayOfRandomNumbers(const int arrayLength)
{
    int* newArray = (int*)calloc(arrayLength, sizeof(int));
    if (newArray == NULL)
    {
        return NULL;
    }
    srand(time(NULL));
    for (size_t i = 0; i < arrayLength; i++)
    {
        newArray[i] = rand() % RANGE_OF_RANDOM_NUMBERS;
    }
    return newArray;
}

int main(void)
{
    const bool testsPassed = tests();
    if (!testsPassed)
    {
        return TESTS_FAILED;
    }

    int arrayLength = 0;
    int amountOfRandomNumbers = 0;
    const bool successfullRead = readData(&arrayLength, &amountOfRandomNumbers);
    if (!successfullRead)
    {
        printf("Error input\n");
        return SCAN_ERROR;
    }

    int* randomArray = createArrayOfRandomNumbers(arrayLength);
    if (randomArray == NULL)
    {
        return OUT_OF_MEMORY;
    }

    quickSort(randomArray, 0, arrayLength - 1);
    for (size_t i = 0; i < amountOfRandomNumbers; i++)
    {
        const int randomNumber = rand() % RANGE_OF_RANDOM_NUMBERS;
        printf(binarySearch(randomNumber, randomArray, arrayLength) == -1 ? "Number %d is not in random array\n": "Number %d is in random array\n", randomNumber);
    }

    free(randomArray);
    return SUCCESS;
}