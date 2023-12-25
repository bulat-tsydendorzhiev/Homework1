#include <stdbool.h>
#include <stdlib.h>

#include "../Stack/Stack/CharStack.h"
#include "advancedBracketBalance.h"

bool compareBrackets(char openingBracket, char closingBracket)
{
    if (openingBracket == '(')
    {
        return closingBracket == ')';
    }
    if (openingBracket == '[')
    {
        return closingBracket == ']';
    }
    if (openingBracket == '{')
    {
        return closingBracket == '}';
    }
}

bool isBalanced(char* string, BalanceError* balanceError)
{
    CharStack* stack = NULL;
    bool closed = false;
    for (int i = 0; string[i] != '\0'; ++i)
    {
        char symbol = string[i];
        if (symbol == '(' || symbol == '[' || symbol == '{')
        {
            if (closed)
            {
                *balanceError = stackError;
                clearCharStack(&stack);
                return false;
            }
            pushChar(&stack, symbol);
        }

        else if (symbol == ')' || symbol == ']' || symbol == '}')
        {
            CharErrorCode errorTop = okCharStack;
            char topBracket = topChar(stack, &errorTop);

            if (errorTop)
            {
                *balanceError = stackError;
                clearCharStack(&stack);
                return false;
            }

            if (!compareBrackets(topBracket, symbol))
            {
                *balanceError = stackError;
                clearCharStack(&stack);
                return false;
            }

            popChar(&stack);
            closed = true;
        }
    }

    if (!charStackIsEmpty(stack))
    {
        *balanceError = stackError;
        clearCharStack(&stack);
        return false;
    }

    clearCharStack(&stack);
    return true;
}
