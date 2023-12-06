#include <stdio.h>

#define MAX_ARRAY_LENGTH 256

size_t countNumberOfZeroElements(const int* const array, const int arrayLength)
{
	size_t numberOfElements = 0;
	for (size_t i = 0; i < arrayLength; i++)
	{
		if (array[i] == 0)
		{
			++numberOfElements;
		}
	}
	return numberOfElements;
}

int main()
{
	int arrayLength = 0;
	printf("Input array length: ");
	if (scanf_s("%d", &arrayLength) != 1 || arrayLength <= 0)
	{
		printf("Error input\n");
		return 1;
	}

	int array[MAX_ARRAY_LENGTH] = { 0 };
	printf("Input array: ");
	for (size_t i = 0; i < arrayLength; i++)
	{
		scanf_s("%d", &array[i]);
	}

	const size_t numberOfZeroElements = countNumberOfZeroElements(array, arrayLength);
	printf("Number of zeroes in array = %Iu\n", numberOfZeroElements);
	return 0;
}