#include <stdlib.h>
#include <stdio.h>

#include "Qsort.h"

static void swap(char* number1, char* number2)
{
    const char temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

static void insertionSort(char* array, int left, int right)
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

void qSort(char* const array, const int left, const int right)
{
    if (right - left + 1 <= 10)
    {
        insertionSort(array, left, right);
        return;
    }
    const char pivot = array[(left + right) / 2];
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
        qSort(array, left, j + 1);
    }
    if (i < right)
    {
        qSort(array, i, right);
    }
}
