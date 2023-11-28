#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>

#define LENGTH_FOR_COMPARE 100000

void swap(int* number1, int* number2)
{
	int temp = *number1;
	*number1 = *number2;
	*number2 = temp;
}

void bubbleSort(int* arrayOfNumbers, const int length)
{
	bool noSwaps = true;
	for (int i = 0; i < length; ++i)
	{
		noSwaps = true;
		for (int j = 0; j < length - i - 1; ++j)
		{
			if (arrayOfNumbers[j] > arrayOfNumbers[j + 1])
			{
				swap(&arrayOfNumbers[j], &arrayOfNumbers[j + 1]);
				noSwaps = false;
			}
		}
		if (noSwaps)
		{
			break;
		}
	}
}

void countingSort(int* arrayOfNumbers, const int length)
{
	int maxElement = INT_MIN, minElement = INT_MAX;
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

	const int newArrayLength = maxElement - minElement + 1;
	int* amountOfNumbers = (int*)calloc(newArrayLength, sizeof(int));
	if (amountOfNumbers == NULL)
	{
		free(amountOfNumbers);
		return;
	}

	for (int i = 0; i < length; ++i)
	{
		amountOfNumbers[arrayOfNumbers[i] - minElement]++;
	}
	for (int i = 0, j = 0; i < newArrayLength; ++i)
	{
		while (amountOfNumbers[i] > 0)
		{
			arrayOfNumbers[j] = i + minElement;
			++j;
			--amountOfNumbers[i];
		}
	}
	free(amountOfNumbers);
}

bool arraysAreEqual(const int* const array1, const int* const array2, const int length)
{
	for (size_t i = 0; i < length; ++i)
	{
		if (array1[i] != array2[i])
		{
			return false;
		}
	}
	return true;
}

bool sortingTest(void (*sortFunction)(int*, const int))
{
	int testCases[][5] = { {-1, -2, -3, -4, -5},
								{1, 2, 3, 4, 5},
								{3, 1, 4, 1, 5},
								{5, 4, 3, 2, 1},
								{0, 0, 0, 0, 0} };
	const int expectedResults[][5] = { {-5, -4, -3, -2, -1},
								{1, 2, 3, 4, 5},
								{1, 1, 3, 4, 5},
								{1, 2, 3, 4, 5},
								{0, 0, 0, 0, 0} };
	const int numberOfTests = sizeof(testCases) / sizeof(testCases[0]);

	for (size_t i = 0; i < numberOfTests; i++)
	{
		const int testCaseArrayLength = sizeof(testCases[i]) / sizeof(testCases[i][0]);
		sortFunction(testCases[i], testCaseArrayLength);
		if (!arraysAreEqual(testCases[i], expectedResults[i], testCaseArrayLength))
		{
			return true;
		}
	}
	return false;
}

int tests(void)
{
	const int errorBubbleSortTest = sortingTest(bubbleSort);
	if (errorBubbleSortTest)
	{
		return -1;
	}

	const int errorCountingSortTest = sortingTest(countingSort);
	if (errorCountingSortTest)
	{
		return -2;
	}

	return 0;
}

void printMeasureSortingTime(int* array1, int* array2, const int arraysLength)
{
	;
	clock_t startOfSorting = clock();
	bubbleSort(array1, arraysLength);
	clock_t endOfSorting = clock();
	double timeUsedForBubbleSort = ((double)(endOfSorting - startOfSorting)) / CLOCKS_PER_SEC;

	printf("Bubble sort took %lf seconds\n", timeUsedForBubbleSort);

	startOfSorting = clock();
	bubbleSort(array2, arraysLength);
	endOfSorting = clock();
	double timeUsedForCountingSort = ((double)(endOfSorting - startOfSorting)) / CLOCKS_PER_SEC;

	printf("Counting sort took %lf seconds\n", timeUsedForCountingSort);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	const int errorSortTest = tests();
	if (errorSortTest)
	{
		return errorSortTest;
	}

	int testArray1[LENGTH_FOR_COMPARE] = { 0 };
	int testArray2[LENGTH_FOR_COMPARE] = { 0 };
	for (int i = 0; i < LENGTH_FOR_COMPARE; ++i)
	{
		testArray1[i] = rand();
		testArray2[i] = rand();
	}

	printMeasureSortingTime(testArray1, testArray2, LENGTH_FOR_COMPARE);
	return 0;
}