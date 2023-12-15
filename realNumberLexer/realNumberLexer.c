#include <stdlib.h>

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
} States;

static bool isDigit(const char character)
{
	return character >= '0' && character <= '9';
}

bool isRealNumber(const char* const string, const size_t length)
{
	States state = 0;
	for (size_t i = 0; i < length + 1; i++)
	{
		switch (state)
		{
		case start:
			if (isDigit(string[i]))
			{
				state = integerPart;
				break;
			}
			return false;
		case integerPart:
			if (isDigit(string[i]))
			{
				state = integerPart;
				break;
			}
			if (string[i] == '.')
			{
				state = point;
				break;
			}
			if (string[i] == 'E')
			{
				state = exponent;
				break;
			}
			return string[i] == '\0';
		case point:
			if (isDigit(string[i]))
			{
				state = fraction;
				break;
			}
			return false;
		case fraction:
			if (isDigit(string[i]))
			{
				state = fraction;
				break;
			}
			if (string[i] == 'E')
			{
				state = exponent;
				break;
			}
			return string[i] == '\0';
		case exponent:
			if (isDigit(string[i]))
			{
				state = remainingNumbers;
				break;
			}
			if (string[i] == '+' || string[i] == '-')
			{
				state = exponentSign;
				break;
			}
			return false;
		case exponentSign:
			if (isDigit(string[i]))
			{
				state = remainingNumbers;
				break;
			}
			return false;
		case remainingNumbers:
			if (isDigit(string[i]))
			{
				state = remainingNumbers;
				break;
			}
			return string[i] == '\0';
		}
	}
}