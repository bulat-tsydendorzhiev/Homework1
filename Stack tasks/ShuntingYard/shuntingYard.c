#include <stdlib.h>

#include "shuntingYard.h"
#include "../Stack/Stack/CharStack.h"

bool isDigit(char symbol)
{
	return symbol >= '0' && symbol <= '9';
}

bool isArithmeticOperation(char symbol)
{
	return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

int operationPriority(char operation)
{
	switch (operation)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default:
		return 0;
	}
}

ErrorCode infixToPostfix(char* infixExpression, char* postfixForm)
{
	CharErrorCode stackErrorCode = okCharStack;
	CharStack* stack = NULL;
	int j = 0;

	for (int i = 0; infixExpression[i] != '\0'; ++i)
	{
		char symbol = infixExpression[i];

		if (symbol == ' ')
		{
			continue;
		}

		if (isDigit(symbol))
		{
			postfixForm[j] = symbol;
			++j;
			postfixForm[j] = ' ';
			++j;
		}
		else if (symbol == '(')
		{
			pushChar(&stack, symbol);
		}
		else if (symbol == ')')
		{
			while (!charStackIsEmpty(stack) && topChar(stack, &stackErrorCode) != '(')
			{
				postfixForm[j] = topChar(stack, &stackErrorCode);
				popChar(&stack);
				++j;
				postfixForm[j] = ' ';
				++j;
			}

			// Deleting opening bracket
			popChar(&stack);
		}
		else if (isArithmeticOperation(symbol))
		{
			while (!charStackIsEmpty(stack) && topChar(stack, &stackErrorCode) != '(' && operationPriority(topChar(stack, &stackErrorCode)) >= operationPriority(symbol))
			{
				postfixForm[j] = topChar(stack, &stackErrorCode);
				popChar(&stack);
				++j;
				postfixForm[j] = ' ';
				++j;
			}

			pushChar(&stack, symbol);
		}
		else
		{
			return inputExpressionError;
		}
	}

	while (!charStackIsEmpty(stack))
	{
		postfixForm[j] = topChar(stack, &stackErrorCode);
		popChar(&stack);
		++j;
		postfixForm[j] = ' ';
		++j;
	}

	postfixForm[j] = '\0';

	return ok;
}
