#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "postfixCalculator.h"
#include "../Stack/Stack/IntStack.h"

static bool isDigit(const char symbol)
{
    return symbol >= '0' && symbol <= '9';
}

static bool isArithmeticOperation(const char symbol)
{
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

static int calculateExpression(const int firstNumber, const int secondNumber, const char arithmeticOperation, ErrorCode* const errorCode)
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

int calculatePostfixArithmeticExpression(const char* const expression, ErrorCode* const errorCode)
{
    IntStack* numbers = NULL;
    IntStackErrorCode stackErrorCode = okIntStack;
    for (size_t i = 0; expression[i] != '\0'; ++i)
    {
        if (isDigit(expression[i - 1]) && expression[i] != ' ')
        {
            *errorCode = inputError;
            clearIntStack(&numbers);
            return inputError;
        }

        const char symbol = expression[i];
        if (symbol == ' ')
        {
            continue;
        }

        if (isDigit(symbol))
        {
            stackErrorCode = pushInt(&numbers, symbol - '0');
            if (stackErrorCode)
            {
                clearIntStack(&numbers);
                return stackError;
            }
        }
        else if (isArithmeticOperation(symbol))
        {
            const int secondNumber = topInt(numbers, &stackErrorCode);
            if (stackErrorCode)
            {
                clearIntStack(&numbers);
                *errorCode = stackError;
                return stackError;
            }
            popInt(&numbers);

            const int firstNumber = topInt(numbers, &stackErrorCode);
            if (stackErrorCode)
            {
                clearIntStack(&numbers);
                *errorCode = stackError;
                return stackError;
            }
            popInt(&numbers);

            const int intermediateResult = calculateExpression(firstNumber, secondNumber, symbol, errorCode);
            if (*errorCode == divisionByZero)
            {
                clearIntStack(&numbers);
                return divisionByZero;
            }

            stackErrorCode = pushInt(&numbers, intermediateResult);
            if (stackErrorCode)
            {
                clearIntStack(&numbers);
                return stackErrorCode;
            }
        }
        else
        {
            *errorCode = inputError;
            clearIntStack(&numbers);
            return inputError;
        }
    }

    const int result = topInt(numbers, &stackErrorCode);
    *errorCode = stackErrorCode ? stackError : ok;
    clearIntStack(&numbers);
    return result;
}
