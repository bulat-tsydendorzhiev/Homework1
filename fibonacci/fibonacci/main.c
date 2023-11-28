#include <stdio.h>
#include <stdbool.h>
#include <time.h>

int recursiveFibonacci(const int number, bool* errorOccured)
{
	if (number < 0)
	{
		*errorOccured = true;
		return -1;
	}
	if (number == 0)
	{
		return 0;
	}
	if (number <= 2)
	{
		return 1;
	}
	return recursiveFibonacci(number - 1, errorOccured) + recursiveFibonacci(number - 2, errorOccured);
}

int iterativeFibonacci(const int number, bool* errorOccured)
{
	if (number < 0)
	{
		*errorOccured = true;
		return -1;
	}
	
	int currentNumber = 0, previousNumber = 1;
	for (size_t i = 0; i < number; ++i)
	{
		currentNumber = currentNumber + previousNumber;
		previousNumber = currentNumber - previousNumber;
	}
	return currentNumber;
}

bool testFunction(const int *const function())
{
	const int expected[] = { -1, 0, 1, 1, 2, 3, 5, 8 };
	const bool expectedErrors[] = { true, false, false, false, false, false, false, false };
	const int numberOfTests = sizeof(expected) / sizeof(expected[0]);
	for (size_t i = 0; i < numberOfTests; ++i)
	{
		bool errorInput = false;
		const int tempResult = function(i - 1, &errorInput);
		if (tempResult != expected[i] || errorInput != expectedErrors[i])
		{
			return true;
		}
	}
	return false;
}

int tests(void)
{
	const int recursiveFibonacciTestError = testFunction(recursiveFibonacci);
	if (recursiveFibonacciTestError)
	{
		return -1;
	}

	const int iterativeFibonacciTestError = testFunction(iterativeFibonacci);
	if (iterativeFibonacciTestError)
	{
		return -2;
	}
	return 0;
}

void timeCompare(void)
{
	bool errorInput = false;
	for (int i = 0; i < 50; ++i)
	{
		clock_t start = clock();
		recursiveFibonacci(i, &errorInput);
		clock_t end = clock();
		const double timeForRecursive = ((double)(end - start)) / CLOCKS_PER_SEC;

		start = clock();
		iterativeFibonacci(i, &errorInput);
		end = clock();
		const double timeForIterative = ((double)(end - start)) / CLOCKS_PER_SEC;

		printf("Fibonacci number = %d | iterative method time = %lf | recursive method time = %lf\n", i, timeForIterative, timeForRecursive);
	}
}

int main()
{
	const int errorTest = tests();
	if (errorTest)
	{
		return errorTest;
	}

	// time compare in interactive mode
	timeCompare();
	return 0;
}