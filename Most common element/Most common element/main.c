#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int writeData(int* arrayLength, int** arrayOfNumbers);
void swap(int* number1, int* number2);
void insertionSort(int* arrayOfNumbers, int left, int right);
void quickSort(int* arrayOfNumbers, int left, int right);
int findMostFrequent(int* arrayOfNumbers, int arrayLength);
int searchTest(void);

int main(void)
{
    setlocale(LC_ALL, "Rus");
    const int errorSearchTest = searchTest();
    if (!errorSearchTest)
    {
        int arrayLength, *arrayofNumbers;
        const int errorWriteData = writeData(&arrayLength, &arrayofNumbers);
        if (!errorWriteData)
        {
            int result = findMostFrequent(&(*arrayofNumbers), arrayLength);
            printf("%d\n", result);
        }
        return errorWriteData;
    }
    return errorSearchTest;
}

int writeData(int* arrayLength, int** arrayOfNumbers)
{
    int amountOfValues;
    char check;

    printf("Введите длину массива чисел: ");
    amountOfValues = scanf_s("%d%c", arrayLength, &check);
    if (*arrayLength <= 0 || amountOfValues != 2 || check != '\n')
    {
        printf("Некорректный ввод данных\n");
        if (*arrayLength <= 0)
        {
            printf("Длина массива должна быть натуральным числом\n");
        }
        return 1;
    }

    printf("Введите сам массив: ");
    *arrayOfNumbers = (int*)malloc(sizeof(int) * *arrayLength);
    for (int i = 0; i < *arrayLength; ++i)
    {
        scanf_s("%d", &(*arrayOfNumbers)[i]);
    }
    return 0;
}

void swap(int* number1, int* number2)
{
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

void insertionSort(int* arrayOfNumbers, int left, int right)
{
    int value, j;
    for (int i = left; i <= right; ++i)
    {
        value = arrayOfNumbers[i];
        j = i;
        while (j > left && arrayOfNumbers[j - 1] > value)
        {
            arrayOfNumbers[j] = arrayOfNumbers[j - 1];
            j--;
        }
        arrayOfNumbers[j] = value;
    }
}

void quickSort(int* arrayOfNumbers, int left, int right)
{
    if (right - left + 1 <= 10)
    {
        insertionSort(arrayOfNumbers, left, right);
        return;
    }
    int pivot = arrayOfNumbers[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j)
    {
        while (arrayOfNumbers[i] < pivot)
        {
            i++;
        }
        while (arrayOfNumbers[j] > pivot)
        {
            j--;
        }

        if (i <= j)
        {
            swap(&arrayOfNumbers[j], &arrayOfNumbers[i]);
            i++;
            j--;
        }
    }

    if (left < j)
    {
        quickSort(arrayOfNumbers, left, j + 1);
    }
    if (i < right)
    {
        quickSort(arrayOfNumbers, i, right);
    }
}

int findMostFrequent(int* arrayOfNumbers, int arrayLength)
{
    quickSort(arrayOfNumbers, 0, arrayLength - 1);

    int answer = arrayOfNumbers[0], maxCount = 1;
    int count = 1;

    for (int i = 1; i < arrayLength; ++i)
    {
        if (arrayOfNumbers[i - 1] == arrayOfNumbers[i])
        {
            count++;
            if (count > maxCount)
            {
                maxCount = count;
                answer = arrayOfNumbers[i - 1];
            }
        }
        else
        {
            count = 1;
        }
    }
    return answer;
}

int searchTest(void)
{
    // Тест 1: Наиболее часто встречающееся число в середине массива
    int array1[] = { 8, 8, 8, 9, 9, 9, 9, 10, 10 }; 
    int length1 = sizeof(array1) / sizeof(array1[0]);
    if (findMostFrequent(array1, length1) != 9)
    {
        return 1;
    }
    
    // Тест 2: Наиболее часто встречающееся число в начале массива
    int array2[] = {5, 5, 5, 5, 6, 6, 7, 7, 7};
    int length2 = sizeof(array2) / sizeof(array2[0]);
    if (findMostFrequent(array2, length2) != 5)
    {
        return 2;
    }
    
    // Тест 3: Наиболее часто встречающееся число в конце массива
    int array3[] = { 1, 2, 2, 3, 3, 3, 4, 4, 4, 4 };
    int length3 = sizeof(array3) / sizeof(array3[0]);
    if (findMostFrequent(array3, length3) != 4)
    {
        return 3;
    }
    
    // Тест 4: Массив с одним элементом
    int array4[] = {11};
    int length4 = sizeof(array4) / sizeof(array4[0]);

    if (findMostFrequent(array4, length4) != 11)
    {
        return 4;
    }
    
    // Тест 5: Массив с повторяющимися числами, но без наиболее часто встречающегося числа
    int array5[] = {12, 12, 13, 13, 14, 14};
    int length5 = sizeof(array5) / sizeof(array5[0]);
    if (findMostFrequent(array5, length5) != 12)
    {
        return 5;
    }

    return 0;
}