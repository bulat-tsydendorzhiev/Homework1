#include <stdlib.h>
#include <stdio.h>

#include "shuntingYardTests.h"
#include "shuntingYard.h"

TestErrorCode tests(void)
{
	char testExpressions[][100] = { "3 + 2",
								"3 + 4 + 2 + 1",
								"3 + 4 * 2 / ( 1 - 5 )",
								"( 3 + 4 ) * ( 2 - 1 )" };
	char expectedResults[][100] = { "3 2 +",
								"3 4 + 2 + 1 +",
								"3 4 2 * 1 5 - / +",
								"3 4 + 2 1 - *" };

	for (int i = 0; i < 5; ++i)
	{
		char* result = malloc(sizeof(char) * 100);
		ErrorCode errorCode = infixToPostfix(testExpressions[0], result);
		if (result != expectedResults[i])
		{
			printf("Test %d failed\n", i + 1);
			return testFailed;
		}
	}
}