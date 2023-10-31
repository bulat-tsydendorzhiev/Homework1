#include <stdio.h>
#include <stdlib.h>

#include "postfixCalculatorTests.h"
#include "postfixCalculator.h"

#define MAX_LENGTH 100

int main(void)
{
	const ErrorTest errorTest = tests();
	if (errorTest)
	{
		return errorTest;
	}

	printf("Input arithmetic expression in postfix form\n");
	char* expression = malloc(sizeof(char) * MAX_LENGTH);
	scanf_s("%[^\n]", expression, MAX_LENGTH - 1);

	ErrorCode errorCode = ok;
	const int result = postfixCalculator(expression, &errorCode);
	if (errorCode == inputError)
	{
		printf("Input error\n");
		return errorCode;
	}
	else if (errorCode == divisionByZero)
	{
		printf("Division by zero. You can't divide by zero.\n");
		return divisionByZero;
	}

	printf("%d\n", result);

	free(expression);
	return 0;
}