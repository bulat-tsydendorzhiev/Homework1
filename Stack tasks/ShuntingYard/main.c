#include <stdio.h>
#include <stdlib.h>

#include "shuntingYardTests.h"
#include "shuntingYard.h"

#define MAX_LENGTH_OF_STRING 100

int main(void)
{
	const TestErrorCode testErrorCode = testPassed;
	if (testErrorCode)
	{
		return testErrorCode;
	}

	char* infixEpression = malloc(sizeof(char) * MAX_LENGTH_OF_STRING);
	char* postfixForm = malloc(sizeof(char) * MAX_LENGTH_OF_STRING);

	printf("Input expression in infix form:\n");
	scanf_s("%[^\n]", infixEpression, MAX_LENGTH_OF_STRING - 1);

	const ErrorCode errorCode = infixToPostfix(infixEpression, postfixForm);
	if (errorCode == inputExpressionError)
	{
		printf("Invalid input\n");
		return inputExpressionError;
	}
	else if (errorCode == bracketError)
	{
		printf("Invalid expression\n");
		return bracketError;
	}
	else
	{
		printf("%s\n", postfixForm);
	}

	return 0;
}