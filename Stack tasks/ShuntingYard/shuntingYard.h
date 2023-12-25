#pragma once
#include <stdbool.h>

#define MAX_STRING_LENGTH 100

typedef enum
{
    ok,
    inputExpressionError,
    openedParenthesesError,
    closedParenthesesError
} ErrorCode;

// Convert the infix form of a number to the postfix form
ErrorCode translateInfixToPostfix(char infixExpression[MAX_STRING_LENGTH], char postfixForm[MAX_STRING_LENGTH]);
