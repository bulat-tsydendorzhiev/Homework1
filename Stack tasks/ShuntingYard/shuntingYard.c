#include <stdlib.h>

#include "shuntingYard.h"
#include "../Stack/Stack/CharStack.h"

static bool isDigit(const char character)
{
    return character >= '0' && character <= '9';
}

static bool isArithmeticOperation(const char character)
{
    return character == '+' || character == '-' || character == '*' || character == '/';
}

static int getOperationPriority(const char operation)
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
        return -1;
    }
}

ErrorCode translateInfixToPostfix(char infixExpression[MAX_STRING_LENGTH], char postfixForm[MAX_STRING_LENGTH])
{
    CharStackErrorCode stackError = okCharStack;
    CharStack* stack = NULL;
    size_t j = 0;
    int parenthesesCount = 0;

    for (size_t i = 0; infixExpression[i] != '\0'; ++i)
    {
        char character = infixExpression[i];

        if (character == ' ')
        {
            continue;
        }

        if (isDigit(character))
        {
            postfixForm[j] = character;
            ++j;
            postfixForm[j] = ' ';
            ++j;
        }
        else if (character == '(')
        {
            pushChar(&stack, character);
            ++parenthesesCount;
        }
        else if (character == ')')
        {
            while (!charStackIsEmpty(stack) && topChar(stack, &stackError) != '(')
            {
                postfixForm[j] = topChar(stack, &stackError);
                popChar(&stack);
                ++j;
                postfixForm[j] = ' ';
                ++j;
            }

            --parenthesesCount;
            popChar(&stack);
        }
        else if (isArithmeticOperation(character))
        {
            while (!charStackIsEmpty(stack) && topChar(stack, &stackError) != '(' &&
                getOperationPriority(topChar(stack, &stackError)) >= getOperationPriority(character))
            {
                postfixForm[j] = topChar(stack, &stackError);
                popChar(&stack);
                ++j;
                postfixForm[j] = ' ';
                ++j;
            }

            pushChar(&stack, character);
        }
        else
        {
            return inputExpressionError;
        }
    }

    if (parenthesesCount != 0)
    {
        return parenthesesCount > 0 ? openedParenthesesError : closedParenthesesError;
    }

    while (!charStackIsEmpty(stack))
    {
        postfixForm[j] = topChar(stack, &stackError);
        popChar(&stack);
        ++j;
        postfixForm[j] = ' ';
        ++j;
    }

    return ok;
}
