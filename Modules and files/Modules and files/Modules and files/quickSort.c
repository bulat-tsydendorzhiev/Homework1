#include "quickSort.h"

static void swap(int* number1, int* number2)
{
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

static void insertionSort(int* const array, const size_t left, const size_t right)
{
    for (size_t i = left; i <= right; ++i)
    {
        int value = array[i];
        size_t j = i;
        while (j > left && array[j - 1] > value)
        {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = value;
    }
}

void quickSort(int* const array, const size_t left, const size_t right)
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