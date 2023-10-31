#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "advancedBracketBalance.h"
#include "advancedBracketBalanceTests.h"

#define MAX_LENGTH 100

int main(void)
{
	const TestErrorCode testErrorCode = tests();
	if (testErrorCode)
	{
		return testErrorCode;
	}

	char* string = malloc(sizeof(char) * MAX_LENGTH);
	printf("Enter bracket sequence: ");
	scanf_s("%[^\n]", string, MAX_LENGTH - 1);

	BalanceError balanceError = balance;
	isBalanced(string, &balanceError);
	if (!balanceError)
	{
		printf("Your bracket sequence is balanced\n");
	}
	else
	{
		printf("Your bracket sequence is not balanced\n");
	}

	free(string);
	return 0;
}