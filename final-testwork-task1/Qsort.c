#include <stdlib.h>
#include <stdio.h>

#include "Qsort.h"

static void swap(int* number1, int* number2)
{
    *number1 ^= *number2;
    *number2 ^= *number1;
    *number1 ^= *number2;
}

static void insertionSort(int* array, int left, int right)
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

void qSort(int* const array, const int left, const int right)
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