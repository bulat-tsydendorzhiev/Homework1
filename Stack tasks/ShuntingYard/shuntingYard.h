#pragma once
#include <stdbool.h>

typedef enum
{
	ok,
	inputExpressionError,
	bracketError
} ErrorCode;

// Function to check a character for a number
bool isDigit(char symbol);

// Function to check a character for an arithmetic operation
bool isArithmeticOperation(char symbol);

// Function to determine the priority of an operation
int operationPriority(char operation);

// Function to convert the infix form of a number to the postfix form
ErrorCode infixToPostfix(char* infixExpression, char* postfixForm);
