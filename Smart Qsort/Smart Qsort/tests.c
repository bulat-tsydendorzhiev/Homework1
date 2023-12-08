#include <stdlib.h>
#include <stdio.h>

#include "tests.h"
#include "smartQsort.h"

static bool isSorted(const int* const array, const size_t arrayLength)
{
	if (arrayLength == 1)
	{
		return true;
	}
	for (size_t i = 1; i < arrayLength; ++i)
	{
		if (array[i - 1] > array[i])
		{
			return false;
		}
	}
	return true;
}

bool tests(void)
{
	int testArrays[][20] = { {1},
						{5, 4, 3, 2, 1},
						{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						{15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
						{1, 3, 2, 0, -1, 5, 6, 7, 2, 9, -12, 68, 37, 21, 99, 214, 62, 63, 12, 0}};
	const size_t testArraysLengths[] = {1, 5, 15, 16, 20};

	for (size_t i = 0; i < 4; ++i)
	{
		smartQsort(testArrays[i], 0, testArraysLengths[i] - 1);
		if (!isSorted(testArrays[i], testArraysLengths[i]))
		{
			return false;
		}
	}
	return true;
}