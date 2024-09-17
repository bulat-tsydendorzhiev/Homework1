#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int findSumOfDigits(int number)
{
	int absoluteNumber = number < 0 ? number * -1 : number;
	int sum = 0;
	while (absoluteNumber > 0)
	{
		sum += absoluteNumber % 10;
		absoluteNumber /= 10;
	}
	return sum;
}

int* findNumbersWithMaxSumOfDigits(const int* numbers, int length, int* count)
{
	int maxSum = 0;
	int* answer = malloc(length * sizeof(int));
	int count1 = 0;

	for (int i = 0; i < length; ++i)
	{
		const int digitSum = findSumOfDigits(numbers[i]);
		if (digitSum > maxSum)
		{
			maxSum = digitSum;
			count1 = 0;
			answer[count1] = numbers[i];
			count1++;
		}
		else if (digitSum == maxSum)
		{
			answer[count1] = numbers[i];
			count1++;
		}
	}
	*count = count1;
	return answer;
}

bool similar(const int *numbers, const int *expected, const int length)
{
	for (int i = 0; i < length; ++i)
	{
		if (numbers[i] != expected[i])
		{
			return false;
		}
	}
	return true;
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
		int count = 0;
		const int length = sizeof(testArray) / sizeof(testArray[0]);
		const int result = findNumbersWithMaxSumOfDigits(testArray[i], length, &count);
		if (!similar(result, expectedResults[i], length))
		{
			return i + 1;
		}
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
	return 0;
}