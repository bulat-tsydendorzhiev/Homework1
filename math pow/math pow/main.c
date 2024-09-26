#include <stdio.h>
#include <stdbool.h>

void readNumber(int* const number, const char* const inputParameter)
{
	printf("Enter integer %s: ", inputParameter);
	int scanAmount = scanf_s("%d", number);
	while (scanAmount != 1)
	{
		printf("Wrong input. Please, try again.");
		scanf_s("%*[^\n]");
		scanAmount = scanf_s("%d", number);
	}
}

void readData(int* const base, int* const power)
{
	readNumber(base, "number");
	readNumber(power, "power of number");
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
	const int errorTest = tests();
	if (errorTest)
	{
		return errorTest;
	}

	int base = 0;
	int power = 0;

	readData(&base, &power);

	bool errorInput = false;
	const double result = fastPow(base, power, &errorInput);
	if (errorInput)
	{
		printf("Incorrect input data\n");
		printf("Uncertain result\n");
		return 1;
	}

	printf("%d to the power of %d equals: %lf\n", base, power, result);

	return 0;
}