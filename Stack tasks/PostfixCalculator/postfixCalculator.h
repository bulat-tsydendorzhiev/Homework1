#pragma once

#include <stdbool.h>

typedef enum
{
    ok,
    inputError,
    divisionByZero = 4,
    stackError
} ErrorCode;

// Calculate arithmetic expression in postfix form
int calculatePostfixArithmeticExpression(const char* const expression, ErrorCode* const errorCode);