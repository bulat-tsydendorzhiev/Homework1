#pragma once
#include <stdbool.h>

typedef enum BalanceError
{
    balance,
    stackError
} BalanceError;

// Function to compare opening and closing brackets
bool compareBrackets(char openingBracket, char closingBracket);

// Function to check the bracket balance in a string
bool isBalanced(char* string, BalanceError* balanceError);
