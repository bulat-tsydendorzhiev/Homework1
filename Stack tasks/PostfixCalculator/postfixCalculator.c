#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "postfixCalculator.h"
#include "../Stack/Stack/IntStack.h"

bool isDigit(char symbol)
{
	return symbol >= '0' && symbol <= '9';
}

bool isArithmeticOperation(char symbol)
{
	return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

int countExpression(const int firstNumber, const int secondNumber, const char arithmeticOperation, ErrorCode* errorCode)
{
	switch (arithmeticOperation)
	{
	case '+':
		return firstNumber + secondNumber;
	case '-':
		return firstNumber - secondNumber;
	case '*':
		return firstNumber * secondNumber;
	case '/':
		if (secondNumber == 0)
		{
			*errorCode = divisionByZero;
			return -1;
		}
		return firstNumber / secondNumber;
	}
}

int postfixCalculator(char* expression, ErrorCode* errorCode)
{
	IntStack* numbers = NULL;
	IntErrorCode intErrorCode = okIntStack;
	for (int i = 0; expression[i] != '\0'; ++i)
	{
		char symbol = expression[i];
		if (symbol == ' ')
		{
			continue;
		}

		if (isDigit(symbol))
		{
			pushInt(&numbers, symbol - '0');
		}
		else if (isArithmeticOperation(symbol))
		{
			const int secondNumber = topInt(numbers, &intErrorCode);
			popInt(&numbers);
			const int firstNumber = topInt(numbers, &intErrorCode);
			popInt(&numbers);
			const int intermediateResult = countExpression(firstNumber, secondNumber, symbol, errorCode);

			if (errorCode == divisionByZero)
			{
				return divisionByZero;
			}

			pushInt(&numbers, intermediateResult);
		}
		else
		{
			*errorCode = inputError;
			clearIntStack(&numbers);
			return inputError;
		}
	}

	const int result = topInt(numbers, &intErrorCode);
	clearIntStack(&numbers);
	return result;
}
