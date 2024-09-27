#include <stdlib.h>

#include "../Stack/Stack/CharStack.h"
#include "advancedBracketBalance.h"

static bool compareBrackets(const char openingBracket, const char closingBracket)
{
    switch (openingBracket)
    {
    case '(':
        return closingBracket == ')';
    case '[':
        return closingBracket == ']';
    case '{':
        return closingBracket == '}';
    default:
        return false;
    }
}

bool isBalanced(const char* const string)
{
    CharStack* stack = NULL;
    for (size_t i = 0; string[i] != '\0'; ++i)
    {
        char character = string[i];
        if (character == '(' || character == '[' || character == '{')
        {
            CharStackErrorCode pushingError = pushChar(&stack, character);
            if (pushingError)
            {
                clearCharStack(&stack);
                return false;
            }
        }
        else if (character == ')' || character == ']' || character == '}')
        {
            CharStackErrorCode errorTop = okCharStack;
            char topBracket = topChar(stack, &errorTop);
            if (errorTop)
            {
                clearCharStack(&stack);
                return false;
            }
            
            if (!compareBrackets(topBracket, character))
            {
                clearCharStack(&stack);
                return false;
            }

            popChar(&stack);
        }
    }

    const bool stackIsEmpty = charStackIsEmpty(stack);
    clearCharStack(&stack);
    return stackIsEmpty;
}
