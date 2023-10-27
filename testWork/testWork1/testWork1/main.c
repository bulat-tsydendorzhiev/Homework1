#include <stdio.h>
#include <stdlib.h>

int* maxSum(const int* subsequence, int length)
{
	int* answer = malloc(sizeof(int) * length);
	int j = 0;
	int maxSum = 0;

	for (int i = 0; i < length; ++i)
	{
		int number = subsequence[i] < 0 ? subsequence[i] * -1: subsequence[i];
		int sumOfDigits = 0;
		while (number > 0)
		{
			sumOfDigits += number % 10;
			number /= 10;
		}
		if (sumOfDigits >= maxSum)
		{
			answer[j] = subsequence[i];
			++j;
			if (sumOfDigits > maxSum)
			{
				answer = malloc(sizeof(int) * length);
				j = 0;
				answer[j] = subsequence[i];
				maxSum = sumOfDigits;
			}
		}
	}
	return answer;
}

void printNumbers(int* result, int length)
{
	for (int i = 0; i < length; ++i)
	{
		printf("%d ", result[i]);
	}
}

int tests(void)
{
	const int testArray[][2] = { {-123},
								{123, 124},
								{124, 124},
								{124, -107} };
	const int expectedResults[][2] = { {-123},
									{124},
									{124, 124},
									{124, -107} };
	for (int i = 0; i < 4; ++i)
	{
		const int length = sizeof(testArray) / sizeof(testArray[0]);
		const int* result = maxSum(testArray[i], length);
		const int expectedResultsLength = sizeof(expectedResults) / sizeof(expectedResults[0]);
		for (int j = 0; j < expectedResultsLength; ++j)
		{
			if (result[j] != expectedResults[j])
			{
				return i + 1;
			}
		}
	}
}

int main(void)
{
	int array1[] = { -123, 123, 124 };
	int length = sizeof(array1) / sizeof(array1[0]);
	const int* result = maxSum(array1, length);
	printNumbers(result, length);
}