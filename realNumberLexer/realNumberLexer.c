#include <stdlib.h>
#include <string.h>

#include "realNumberLexer.h"

typedef enum
{
    start,
    integerPart,
    point,
    fraction,
    exponent,
    exponentSign,
    remainingNumbers
} State;

static bool isDigit(const char character)
{
    return character >= '0' && character <= '9';
}

static bool startMethod(const char character, State* const state)
{
    if (isDigit(character))
    {
        *state = integerPart;
        return false;
    }
    return true;
}

static bool integerPartMethod(const char character, State* const state)
{
    if (isDigit(character))
    {
        *state = integerPart;
        return false;
    }
    if (character == '.')
    {
        *state = point;
        return false;
    }
    if (character == 'E')
    {
        *state = exponent;
        return false;
    }
    return true;
}

static bool pointMethod(const char character, State* const state)
{
    if (isDigit(character))
    {
        *state = fraction;
        return false;
    }
    return true;
}

static bool fractionMethod(const char character, State* const state)
{
    if (isDigit(character))
    {
        *state = fraction;
        return false;
    }
    if (character == 'E')
    {
        *state = exponent;
        return false;
    }
    return true;
}

static bool exponentMethod(const char character, State* const state)
{
    if (isDigit(character))
    {
        *state = remainingNumbers;
        return false;
    }
    if (character == '+' || character == '-')
    {
        *state = exponentSign;
        return false;
    }
    return true;
}

static bool exponentSignMethod(const char character, State* const state)
{
    if (isDigit(character))
    {
        *state = remainingNumbers;
        return false;
    }
    return true;
}

static bool remainingNumbersMethod(const char character, State* const state)
{
    if (isDigit(character))
    {
        *state = remainingNumbers;
        return false;
    }
    return true;
}

bool isRealNumber(const char* const string)
{
    const size_t length = strlen(string);
    State state = start;
    for (size_t i = 0; i < length + 1; ++i)
    {
        switch (state)
        {
        case start:
        {
            const bool exitCode = startMethod(string[i], &state);
            if (exitCode)
            {
                return false;
            }
            break;
        }
        case integerPart:
        {
            const bool exitCode = integerPartMethod(string[i], &state);
            if (exitCode)
            {
                return string[i] == '\0';
            }
            break;
        }
        case point:
        {
            const bool exitCode = pointMethod(string[i], &state);
            if (exitCode)
            {
                return false;
            }
            break;
        }
        case fraction:
        {
            const bool exitCode = fractionMethod(string[i], &state);
            if (exitCode)
            {
                return string[i] == '\0';
            }
            break;
        }
        case exponent:
        {
            const bool exitCode = exponentMethod(string[i], &state);
            if (exitCode)
            {
                return false;
            }
            break;
        }
        case exponentSign:
        {
            const bool exitCode = exponentSignMethod(string[i], &state);
            if (exitCode)
            {
                return false;
            }
            break;
        }
        case remainingNumbers:
        {
            const bool exitCode = exponentSignMethod(string[i], &state);
            if (exitCode)
            {
                return string[i] == '\0';
            }
            break;
        }
        }
    }
}