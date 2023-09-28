#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void swap(int* number1, int* number2);
void bubbleSort(int* arrayOfNumbers, int length);
void countingSort(int* arrayOfNumbers, int length);
void measureSortingTime(int* array1, int array1Length, int* array2, int array2Length);
int bubbleSortTest(void);
int countingSortTest(void);
int sortTest(void);

int main(void)
{
	setlocale(LC_ALL, "Rus");
	const int errorSortTest = sortTest();
	if (!errorSortTest)
	{
		// создаем 2 массива для замера времени работы сортировок
		int testArray1[100000] = { 0 };
		int testArray2[100000] = { 0 };
		for (int i = 0; i < 100000; ++i)
		{
			testArray1[i] = rand() % 5732;
			testArray2[i] = testArray1[i];
		}

		// печатаем затраченное на сортировки время
		measureSortingTime(&testArray1, 100000, &testArray2, 100000);
		return 0;
	}
	return errorSortTest;
}

void swap(int* number1, int* number2)
{
	int temp = *number1;
	*number1 = *number2;
	*number2 = temp;
}

void bubbleSort(int* arrayOfNumbers, int length)
{
	int noSwaps; // для проверки свапа элементов
	for (int i = 0; i < length; ++i)
	{
		noSwaps = 1;
		for (int j = 0; j < length - i - 1; ++j)
		{
			if (arrayOfNumbers[j] > arrayOfNumbers[j + 1])
			{
				swap(&arrayOfNumbers[j], &arrayOfNumbers[j + 1]);
				noSwaps = 0;
			}
		}
		if (noSwaps) // проверка на отсортированный массив
		{
			break;
		}
	}
}

void countingSort(int* arrayOfNumbers, int length)
{
	// ищем максимальный и минимальный элементы для вычисления длины вспомогательного массива
	int maxElement = 0, minElement = 0;
	for (int i = 0; i < length; ++i)
	{
		if (arrayOfNumbers[i] > maxElement)
		{
			maxElement = arrayOfNumbers[i];
		}
		if (arrayOfNumbers[i] < minElement)
		{
			minElement = arrayOfNumbers[i];
		}
	}

	int newArrayLength = maxElement - minElement + 1;
	int* amountOfNumbers = calloc(newArrayLength, sizeof(int));
	// сохраняем количество встреченных чисел в amountOfNumbers
	for (int i = 0; i < length; ++i)
	{
		amountOfNumbers[arrayOfNumbers[i] - minElement]++;
	}

	// сортируем массив, заменяя j-ый элемент на i + minElement
	for (int i = 0, j = 0; i < newArrayLength; ++i)
	{
		while (amountOfNumbers[i] > 0)
		{
			arrayOfNumbers[j++] = i + minElement;
			amountOfNumbers[i]--;
		}
	}
}

int bubbleSortTest(void)
{
	// Тест 1: Одноэлементный массив
	int array1[] = { 5 };
	int length1 = sizeof(array1) / sizeof(array1[0]);
	bubbleSort(array1, length1);
	if (array1[0] != 5) {
		return 1;
	}

	// Тест 2: Массив с повторяющимися элементами
	int array2[] = { 3, 2, 4, 2, 1 };
	int length2 = sizeof(array2) / sizeof(array2[0]);
	bubbleSort(array2, length2);
	if (array2[0] != 1 || array2[1] != 2 || array2[2] != 2 || array2[3] != 3 || array2[4] != 4) {
		return 2;
	}

	// Тест 3: Упорядоченный в обратном порядке массив
	int array3[] = { 9, 7, 5, 3, 1 };
	int length3 = sizeof(array3) / sizeof(array3[0]);
	bubbleSort(array3, length3);
	if (array3[0] != 1 || array3[1] != 3 || array3[2] != 5 || array3[3] != 7 || array3[4] != 9) {
		return 3;
	}

	return 0;
}

int countingSortTest(void)
{
	// Тест 1: Одноэлементный массив
	int array1[] = { 5 };
	int length1 = sizeof(array1) / sizeof(array1[0]);
	bubbleSort(array1, length1);
	if (array1[0] != 5) {
		return 1;
	}

	// Тест 2: Массив с повторяющимися элементами
	int array2[] = { 3, 2, 4, 2, 1 };
	int length2 = sizeof(array2) / sizeof(array2[0]);
	bubbleSort(array2, length2);
	if (array2[0] != 1 || array2[1] != 2 || array2[2] != 2 || array2[3] != 3 || array2[4] != 4) {
		return 2;
	}

	// Тест 3: Упорядоченный в обратном порядке массив
	int array3[] = { 9, 7, 5, 3, 1 };
	int length3 = sizeof(array3) / sizeof(array3[0]);
	bubbleSort(array3, length3);
	if (array3[0] != 1 || array3[1] != 3 || array3[2] != 5 || array3[3] != 7 || array3[4] != 9) {
		return 3;
	}

	return 0;
}

void measureSortingTime(int* array1, int array1Length, int* array2, int array2Length)
{
	clock_t startOfBubbleSort, endOfBubbleSort;
	clock_t startOfCountingSort, endOfCountingSort;
	double timeUseForBubbleSort, timeUseForCountingSort;

	// вычисление затраченного времени в секундах на сортировку массива "Пузырьком"
	startOfBubbleSort = clock();
	bubbleSort(array1, array1Length);
	endOfBubbleSort = clock();
	timeUseForBubbleSort = ((double)(endOfBubbleSort - startOfBubbleSort)) / CLOCKS_PER_SEC;

	// выводим затраченное время
	printf("Сортировка пузырьком заняла %f секунд\n", timeUseForBubbleSort);

	// вычисление затраченного времени в секундах на сортировку массива "Подсчетом"
	startOfBubbleSort = clock();
	bubbleSort(array2, array2Length);
	endOfBubbleSort = clock();
	timeUseForCountingSort = ((double)(endOfBubbleSort - startOfBubbleSort)) / CLOCKS_PER_SEC;

	// выводим затраченное время
	printf("Сортировка подсчетом заняла %f секунд\n", timeUseForCountingSort);
}

int sortTest(void)
{
	const int errorBubbleSortTest = bubbleSortTest();
	if (errorBubbleSortTest)
	{
		printf("Ошибка пузырькойвой сортировки");
		return errorBubbleSortTest;
	}
	const int errorcountingSortTest = countingSortTest();
	if (errorcountingSortTest)
	{
		printf("Ошибка сортировки подсчетом");
		return errorcountingSortTest;
	}
}
