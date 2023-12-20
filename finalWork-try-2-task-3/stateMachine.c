#include <stdlib.h>
#include <string.h>

#include "stateMachine.h"

typedef enum
{
    start,
    end
} State;

static bool isLetter(const char character)
{
    return (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z');
}

static bool isDigit(const char character)
{
    return character >= '0' && character <= '9';
}

bool isRightString(const char* const string)
{
    const size_t length = strlen(string);
    State state = start;
    for (size_t i = 0; i < length + 1; ++i)
    {
        switch (state)
        {
        case start:
            if (isLetter(string[i]))
            {
                state = end;
                break;
            }
            return false;
        case end:
            if (isLetter(string[i]) || isDigit(string[i]) || string[i] == '_')
            {
                state = end;
                break;
            }
            return string[i] == '\0';
        }
    }
}