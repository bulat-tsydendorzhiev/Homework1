#pragma once

// функция меняет местами значения дувх переменных
void swap(char* number1, char* number2)
{
    char temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

// сортировка вставками
void insertionSort(char* symbols, int left, int right)
{
    int value, j;
    for (int i = left; i <= right; ++i)
    {
        value = symbols[i];
        j = i;
        while (j > left && symbols[j - 1] > value)
        {
            symbols[j] = symbols[j - 1];
            j--;
        }
        symbols[j] = value;
    }
}

// быстрая сортировка
void quickSort(char* symbols, int left, int right)
{
    if (right - left + 1 <= 10)
    {
        insertionSort(symbols, left, right);
        return;
    }
    char pivot = symbols[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j)
    {
        while (symbols[i] < pivot)
        {
            i++;
        }
        while (symbols[j] > pivot)
        {
            j--;
        }

        if (i <= j)
        {
            swap(&symbols[j], &symbols[i]);
            i++;
            j--;
        }
    }

    if (left < j)
    {
        quickSort(symbols, left, j + 1);
    }
    if (i < right)
    {
        quickSort(symbols, i, right);
    }
}