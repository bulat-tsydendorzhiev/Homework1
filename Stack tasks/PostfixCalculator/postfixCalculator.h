#pragma once
#include <stdbool.h>

typedef enum ErrorCode
{
	ok,
	inputError,
	divisionByZero
} ErrorCode;

// Function to determine whether a symbol is a digit
bool isDigit(char symbol);

// Function to determine whether a symbol is an arithmetic operation
bool isArithmeticOperation(char symbol);

// Function for calculating the value of an arithmetic operation
int countExpression(const int firstNumber, const int secondNumber, const char arithmeticOperation, ErrorCode* errorCode);

// Function to calculate arithmetic expression in postfix form
int postfixCalculator(char* expression, ErrorCode* errorCode);