#include <stdio.h>
#include <stdbool.h>

void readData(double* number, int* power)
{
	printf("Enter number: ");
	int scanResult = scanf_s("%lf", number);
	while (scanResult == 0)
	{
		scanf_s("%*[^\n]");
		printf("Wrong input! Please enter number: ");
		scanResult = scanf_s("%lf", number);
	}

	printf("Enter number power(integer number): ");
	scanResult = scanf_s("%d", power);
	while (scanResult == 0)
	{
		scanf_s("%*[^\n]");
		printf("Wrong input! Please enter integer number: ");
		scanResult = scanf_s("%d", power);
	}
}

double slowPow(double number, int power, bool* errorOccurred)
{
	if (number == 0 && power <= 0)
	{
		*errorOccurred = true;
		return -1;
	}

	double result = 1.0;
	number = power >= 0 ? number : 1 / number;
	power = power >= 0 ? power : -power;

	for (size_t i = 0; i < power; ++i)
	{
		result *= number;
	}

	return result;
}

double fastPow(double number, int power, bool* errorOccurred)
{
	if (number == 0 && power <= 0)
	{
		*errorOccurred = true;
		return -1;
	}

	double result = 1.0;
	number = power >= 0 ? number : 1 / number;
	power = power >= 0 ? power : -power;

	while (power > 0)
	{
		if (power & 1)
		{
			result *= number;
		}
		number *= number;
		power >>= 1;
	}

	return result;
}

bool testFunction(double (*function)(double, int, bool*))
{
	// first element = number, second element = power, third element = expected result from function 
	const double testCases[][3] = { {0, -1, -1},
									{0, 0, -1},
									{2, 2, 4},
									{2, -2, 0.25},
									{-3, 3, -27},
									{123456789, 0, 1},
									{0, 1241325, 0},
									{1, -124124, 1},
									{1, 123521, 1} };
	const bool expectedErrors[] = { true, true, false, false, false, false, false, false, false };
	const size_t numberOfTests = sizeof(testCases) / sizeof(testCases[0]);

	for (size_t i = 0; i < numberOfTests; ++i)
	{
		bool errorInput = false;
		double tempResult = function(testCases[i][0], (int)testCases[i][1], &errorInput);
		if (tempResult != testCases[i][2] || errorInput != expectedErrors[i])
		{
			return true;
		}
	}
	return false;
}

int tests(void)
{
	const bool slowPowTestError = testFunction(slowPow);
	if (slowPowTestError)
	{
		return -1;
	}

	const bool fastPowTestError = testFunction(fastPow);
	if (fastPowTestError)
	{
		return -2;
	}

	return 0;
}

int main(void)
{
	system("chcp 1251 > nul");

	const int errorTest = tests();
	if (errorTest)
	{
		return errorTest;
	}

	double number = 1.0;
	int power = 1;
	readData(&number, &power);

	bool errorInput = false;
	const double result = fastPow(number, power, &errorInput);
	if (errorInput)
	{
		printf("Uncorrect input data\n");
		printf("Uncertain result\n");
		return 1;
	}

	printf("%lf\n", result);

	return 0;
}