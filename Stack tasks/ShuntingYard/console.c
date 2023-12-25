#include <stdio.h>

#include "console.h"
#include "shuntingYard.h"

ConsoleError runProgram(void)
{
    char infixEpression[MAX_STRING_LENGTH] = "";
    char postfixForm[MAX_STRING_LENGTH] = "";

    printf("Enter expression in infix form: ");
    if (scanf_s("%[^\n]", infixEpression, MAX_STRING_LENGTH - 1) != 1)
    {
        printf("String entry error\n");
        return scanError;
    }

    const ErrorCode errorCode = translateInfixToPostfix(infixEpression, postfixForm);
    switch (errorCode)
    {
    case ok:
        printf("Postfix form: %s\n", postfixForm);
        break;
    case inputExpressionError:
        printf("Invalid input\n");
        break;
    case openedParenthesesError:
    case closedParenthesesError:
        printf("Invalid expression: ");
        printf(errorCode == openedParenthesesError ? "Opened bracket error\n" : "Closed bracket error\n");
        break;
    default:
        printf("Error occured\n");
        break;
    }
    return errorCode;
}