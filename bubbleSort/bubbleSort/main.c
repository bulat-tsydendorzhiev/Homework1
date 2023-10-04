#include <stdio.h>
#include <stdlib.h>

int writeData(int **arrayOfNumbers, int *arrayLength)
{
	printf("Input array's length: ");
	scanf_s("%d", arrayLength);

	*arrayOfNumbers = (int*)malloc(sizeof(int) * *arrayLength);
	printf("Input array: ");
	for (int i = 0; i < *arrayLength; ++i)
	{
		scanf_s("%d", &(*arrayOfNumbers)[i]);
	}
}

void printArray(int *arrayOfNumbers, int arrayLength)
{
	for (int i = 0; i < arrayLength; ++i)
	{
		printf("%d ", arrayOfNumbers[i]);
	}
	printf("\n");
}

void swap(int *number1, int *number2)
{
	int temp = *number1;
	*number1 = *number2;
	*number2 = temp;
}

void bubbleSort(int* arrayOfNumbers, int length)
{
	int noSwaps; // для проверки свапа элементов
	for (int i = 0; i < length; i += 2)
	{
		noSwaps = 1;
		for (int j = 0; j < length - i - 2; j += 2)
		{
			if (arrayOfNumbers[j] > arrayOfNumbers[j + 2])
			{
				swap(&arrayOfNumbers[j], &arrayOfNumbers[j + 2]);
				noSwaps = 0;
			}
		}
		if (noSwaps) // проверка на отсортированный массив
		{
			break;
		}
	}
}

int arraysEqual(int* array1, int* array2, int length)
{
	for (int i = 0; i < length; ++i)
	{
		if (array1[i] != array2[i])
		{
			return 0;
		}
	}
	return 1;
}

int tests(void)
{
	// тест 1:массив нечетной длины
	int array1[] = {5,4,3,2,1};
	int length1 = sizeof(array1) / sizeof(int);
	bubbleSort(array1, length1);
	int expected1[] = {1,4,3,2,5};
	if (!arraysEqual(array1, expected1, length1))
	{
		return 1;
	}

	// тест 2:массив четной длины
	int array2[] = { 6,5,4,3,2,1 };
	int length2 = sizeof(array2) / sizeof(int);
	bubbleSort(array2, length2);
	int expected2[] = { 2,5,4,3,6,1 };
	if (!arraysEqual(array2, expected2, length2))
	{
		return 2;
	}

	// тест 3: одноэлементый массив 
	int array3[] = { 1 };
	int length3 = sizeof(array3) / sizeof(int);
	bubbleSort(array3, length3);
	int expected3[] = { 1 };
	if (!arraysEqual(array3, expected3, length3))
	{
		return 3;
	}

	// тест 4: все элементы равны
	int array4[] = { 1,1,1,1,1 };
	int length4 = sizeof(array4) / sizeof(int);
	bubbleSort(array4, length4);
	int expected4[] = { 1,1,1,1,1 };
	if (!arraysEqual(array4, expected4, length4))
	{
		return 4;
	}
	return 0;
}

int main(void)
{
	int arrayLength;
	int* arrayOfNumbers;
	
	const int errorTest = tests();
	if (!errorTest)
	{
		writeData(&arrayOfNumbers, &arrayLength);
		printArray(arrayOfNumbers, arrayLength);
		bubbleSort(arrayOfNumbers, arrayLength);
		printArray(arrayOfNumbers, arrayLength);
	}
	return errorTest;
}