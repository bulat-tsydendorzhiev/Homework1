#include <stdlib.h>

#include "tests.h"
#include "stateMachine.h"

bool runTests(void)
{
    const char testStrings[][30] = { "123", "A", "a_123", "", "I_am_Banana_1000_minus_9"};
	const bool expectedResults[] = {false, true, true, false, true};

	for (size_t i = 0; i < 5; ++i)
	{
		if (isRightString(testStrings[i]) != expectedResults[i])
		{
			return false;
		}
	}
	return true;
}
