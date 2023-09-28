#include <stdio.h>
#include <time.h>

int iterativeFibonacci(int number);
int recursiveFibonacci(int number);
int testForRecursiveFibonacci(void);
int testForIterativeFibonacci(void);
int tests(void);
void timeCompare(void);

int main(void)
{
	const int errorTest = tests();
	if (errorTest)
	{
		return errorTest;
	}
	printf("Tests passed successfully!\n");
	timeCompare();
	return 0;
}

int iterativeFibonacci(int number)
{
	if (number == 0)
	{
		return 0;
	}
	if (number <= 2)
	{
		return 1;
	}
	else
	{
		int firstPrevious = 1, secondPrevious = 1; // для сохранения двух предыдущих результатов 
		int result;
		for (int i = 0; i < number - 2; ++i)
		{
			result = firstPrevious + secondPrevious;
			firstPrevious = secondPrevious;
			secondPrevious = result;
		}
		return result;
	}
}

int recursiveFibonacci(int number)
{
	if (number == 0)
	{
		return 0;
	}
	if (number <= 2)
	{
		return 1;
	}
	return recursiveFibonacci(number - 1) + recursiveFibonacci(number - 2);
}

int testForRecursiveFibonacci(void)
{
	// Тест 1: Проверка первого числа Фибоначчи
	if (recursiveFibonacci(0) != 0) {
		return 1;
	}

	// Тест 2: Проверка второго числа Фибоначчи
	if (recursiveFibonacci(1) != 1) {
		return 2;
	}

	// Тест 3: Проверка третьего числа Фибоначчи
	if (recursiveFibonacci(2) != 1) {
		return 3;
	}

	// Тест 4: Проверка пятого числа Фибоначчи
	if (recursiveFibonacci(4) != 3) {
		return 4;
	}

	// Тест 5: Проверка десятого числа Фибоначчи
	if (recursiveFibonacci(9) != 34) {
		return 5;
	}

	return 0;
}

int testForIterativeFibonacci(void)
{
	// Тест 1: Проверка первого числа Фибоначчи
	if (iterativeFibonacci(0) != 0) {
		return 1;
	}

	// Тест 2: Проверка второго числа Фибоначчи
	if (iterativeFibonacci(1) != 1) {
		return 2;
	}

	// Тест 3: Проверка третьего числа Фибоначчи
	if (iterativeFibonacci(2) != 1) {
		return 3;
	}

	// Тест 4: Проверка пятого числа Фибоначчи
	if (iterativeFibonacci(4) != 3) {
		return 4;
	}

	// Тест 5: Проверка десятого числа Фибоначчи
	if (iterativeFibonacci(9) != 34) {
		return 5;
	}

	return 0;
}

int tests(void)
{
	// проверка на ошибку у рекурсивного метода
	const int errorRecursiveTest = testForRecursiveFibonacci();
	if (errorRecursiveTest)
	{
		printf("Error of recursive Fibonacci algorithm test\n");
		return errorRecursiveTest;
	}

	// проверка на ошибку у итеративного метода
	const int errorIterativeTest = testForRecursiveFibonacci();
	if (errorIterativeTest)
	{
		printf("Error of iterative Fibonacci algorithm test\n");
		return errorIterativeTest;
	}
}

void timeCompare(void)
{
	// сравниваем время рекурсивного и итеративного способов
	clock_t start, end;
	double timeForRecursive, timeForIterative;

	for (int i = 0; i < 50; ++i)
	{
		// считаем время для рекурсивного способа
		start = clock();
		recursiveFibonacci(i);
		end = clock();
		timeForRecursive = ((double)(end - start)) / CLOCKS_PER_SEC;

		// считаем время для итеративного способа
		start = clock();
		iterativeFibonacci(i);
		end = clock();
		timeForIterative = ((double)(end - start)) / CLOCKS_PER_SEC;

		//выводим их время
		printf("%d Fibonacci number took for iterative took %lf and took for recursive \n", i, timeForRecursive, timeForIterative);
	}
}