#include <stdio.h>

#include "postfixCalculatorTests.h"
#include "postfixCalculator.h"

ErrorTest tests(void)
{
	char testExpressions[][14] = { "3 5 +", "5 2 3 * +", "8 4 2 / 5 * +", "2 5 -" };
	const int expectedResults[] = { 8,11,18,-3 };
	for (int i = 0; i < 4; ++i)
	{
		ErrorCode errorCode = testPassed;
		const int testExpressionResult = postfixCalculator(testExpressions[i], &errorCode);
		if (testExpressionResult != expectedResults[i])
		{
			printf("Test %d failed\n", i + 1);
			return testFailed;
		}
	}
	return testPassed;
}