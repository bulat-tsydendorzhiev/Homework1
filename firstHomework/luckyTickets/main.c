#include <stdio.h>

size_t countLuckyTickets(void)
{
	size_t result = 0, sumOfDigits = 0;
	size_t sums[28] = { 0 };

	for (size_t i = 0; i < 1000; ++i)
	{
		sumOfDigits = i / 100 + (i % 100) / 10 + i % 10;
		sums[sumOfDigits]++;
	}
	for (size_t i = 0; i < 14; ++i)
	{
		result += sums[i] * sums[i];
	}

	return 2 * result;
}

int main()
{
    const size_t numberOfLuckyTickets = countLuckyTickets();
    printf("Six-digit number of lucky tickets = %Iu\n", numberOfLuckyTickets);
	return 0;
}