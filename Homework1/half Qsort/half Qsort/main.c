#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

void swap(int* number1, int* number2);
void halfQsort(int* arrayOfNumbers, int left, int right);
void printArray(int* arrayOfNumbers, int length);
int writeAndCheckData(int* arrayLength);
void createArrayOfRandomNumbers(int* arrayOfNumbers, int length);
void printResult(int* arrayOfNumbers, int length);
int halfQsortTests(void);
int arraysEqual(int* arrayOfNumbers, int* expected, int length);

int main(void)
{
	setlocale(LC_ALL, "Rus");
	int arrayLength;
	const int errorCode = writeAndCheckData(&arrayLength);
	if (!errorCode)
	{
		const int errorHalfQsortTest = halfQsortTests();
		if (!errorHalfQsortTest)
		{
			int* arrayOfNumbers = malloc(sizeof(int) * arrayLength);
			createArrayOfRandomNumbers(arrayOfNumbers, arrayLength);
			printResult(arrayOfNumbers, arrayLength);
			free(arrayOfNumbers);
			return 0;
		}
		return errorHalfQsortTest;
	}
	return errorCode;
}

int writeAndCheckData(int* arrayLength)
{
	// функция ввода и проверки данных
	printf("Введите длину массива: ");
	const int amountOfElements = scanf_s("%d", arrayLength);
	if (amountOfElements != 1 || *arrayLength < 0)
	{
		if (*arrayLength < 0)
		{
			printf("Ошибка: длина массива должна быть неотрицательным числом \n");
			return 2;
		}
		else
		{
			printf("Ошибка: введены некорректные данные");
			return 1;
		}
	}
	return 0;
}

void createArrayOfRandomNumbers(int* arrayOfNumbers, int length)
{
	for (int i = 0; i < length; ++i)
	{
		arrayOfNumbers[i] = rand();
	}
}

void swap(int* number1, int* number2)
{
	int temp = *number1;
	*number1 = *number2;
	*number2 = temp;
}

void halfQsort(int* arrayOfNumbers, int left, int right)
{
	// функция для перемещения чисел меньше опорного элемента в начало массива,
	// а больше - в конец
	int pivot = arrayOfNumbers[(int)((left + right) / 2)]; // опорный элемент для сравнения
	printf("pivot = %d\n", pivot);
	while (left <= right)
	{
		while (arrayOfNumbers[left] < pivot)
		{
			left++; // сдвигаем правый указатель, пока не найдем меньше pivot
		}
		while (arrayOfNumbers[right] > pivot)
		{
			right--; // сдвигаем левый указатель, пока не найдем больше pivot
		}

		if (left <= right)
		{
			// меняем местами больший элемент массива с меньшим и сдвигаем указатели,
			// чтобы не застрять в бесконечном цикле
			swap(&arrayOfNumbers[left], &arrayOfNumbers[right]);
			left++;
			right--;
		}
	}
}

void printArray(int* arrayOfNumbers, int length)
{
	for (int i = 0; i < length; ++i)
	{
		printf("%d ", arrayOfNumbers[i]);
	}
	printf("\n");
}

void printResult(int* arrayOfNumbers, int length)
{
	// выводим массив до и после выполнения кусорта
	printf("Массив до: ");
	printArray(arrayOfNumbers, length);
	halfQsort(arrayOfNumbers, 0, length - 1);
	printf("Массив после: ");
	printArray(arrayOfNumbers, length);
}

int arraysEqual(int* arrayOfNumbers, int* expected, int length)
{
	// возвращает 1 при истине, в противном случае - 0
	for (int i = 0; i < length; ++i)
	{
		if (arrayOfNumbers[i] != expected[i])
		{
			return 0;
		}
	}
	return 1;
}

int halfQsortTests(void)
{
	// Тест 1: Проверка сортировки массива из одного элемента
	int array1[] = { 5 };
	int expected1[] = { 5 };
	halfQsort(&array1, 0, 0);
	if (!arraysEqual(&array1, &expected1, 1)) {
		return 1;
	}

	// Тест 2: Проверка сортировки массива с повторяющимися элементами
	int array2[] = { 7,3,5,3,2 };
	int expected2[] = { 2,3,3,5,7 };
	halfQsort(&array2, 0, 4);
	if (!arraysEqual(&array2, &expected2, 5)) {
		return 2;
	}

	// Тест 3: Проверка сортировки упорядоченного по возрастанию массива
	int array3[] = { 1,2,3,4,5 };
	int expected3[] = { 1,2,3,4,5 };
	halfQsort(&array3, 0, 4);
	if (!arraysEqual(&array3, &expected3, 5)) {
		return 3;
	}

	// Тест 4: Проверка сортировки упорядоченного по убыванию массива
	int array4[] = { 5,4,3,2,1 };
	int expected4[] = { 1,2,3,4,5 };
	halfQsort(&array4, 0, 4);
	if (!arraysEqual(&array4, &expected4, 5)) {
		return 4;
	}

	// Тест 5: Проверка сортировки массива с нечетным количеством элементов
	int array5[] = { 9,4,7,2,1 };
	int expected5[] = { 1,4,2,7,9 };
	halfQsort(&array5, 0, 4);
	if (!arraysEqual(&array5, &expected5, 5)) {
		return 5;
	}

	// Тест 6: Проверка сортировки массива с четным количеством элементов
	int array6[] = { 6,3,8,2 };
	int expected6[] = { 2,3,8,6 };
	halfQsort(&array6, 0, 3);
	if (!arraysEqual(&array6, &expected6, 4)) {
		return 6;
	}

	return 0;
}
