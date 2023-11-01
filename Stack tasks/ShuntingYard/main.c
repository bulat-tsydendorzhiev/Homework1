#include <stdio.h>
#include <stdlib.h>

#include "shuntingYardTests.h"
#include "shuntingYard.h"

#define MAX_LENGTH_OF_STRING 100

int main(void)
{
	const TestErrorCode testErrorCode = tests();
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
		free(infixEpression);
		free(postfixForm);
		return inputExpressionError;
	}
	else if (errorCode == openedParenthesesError || errorCode == closedParenthesesError)
	{
		printf("Invalid expression: ");
		printf(errorCode == openedParenthesesError ? "opened bracket error\n" : "closed bracket error\n");
		free(infixEpression);
		free(postfixForm);
		return errorCode;
	}
	else
	{
		printf("%s\n", postfixForm);
		free(infixEpression);
		free(postfixForm);
	}

	return 0;
}