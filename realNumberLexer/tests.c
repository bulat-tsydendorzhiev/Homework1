#include <stdlib.h>

#include "tests.h"
#include "realNumberLexer.h"

bool runTests(void)
{
	const char correctTestCases[][15] = { "123", "45.6", "3.14159E-20", "6.022E+23" };
	const size_t lengths[] = { 3, 4, 11, 9 };
	for (size_t i = 0; i < 4; ++i)
	{
		if (!isRealNumber(correctTestCases[i], lengths[i]))
		{
			return false;
		}
	}
	return true;
}