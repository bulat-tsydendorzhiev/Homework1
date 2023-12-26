#include <stdio.h>
#include <stdlib.h>

#include "tests.h"
#include "postfixCalculator.h"

#define TESTS_FAILED -1
#define MAX_LENGTH_OF_EXPRESSION 100

int main(void)
{
    const bool testsPassed = runTests();
    if (!testsPassed)
    {
        return TESTS_FAILED;
    }

    printf("Input arithmetic expression in postfix form: ");
    char expression[MAX_LENGTH_OF_EXPRESSION] = "";
    scanf_s("%[^\n]", expression, MAX_LENGTH_OF_EXPRESSION - 1);

    ErrorCode errorCode = ok;
    const int result = calculatePostfixArithmeticExpression(expression, &errorCode);
    switch (errorCode)
    {
    case ok:
        printf("Calculated result = %d\n", result);
        break;
    case inputError:
        printf("Input error\n");
        break;
    case divisionByZero:
        printf("Division by zero. You can't divide by zero.\n");
        break;
    default:
        printf("Error occurred\n");
        break;
    }

    return errorCode;
}