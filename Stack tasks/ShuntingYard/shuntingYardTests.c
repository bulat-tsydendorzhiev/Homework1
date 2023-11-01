#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "shuntingYardTests.h"
#include "shuntingYard.h"

TestErrorCode tests(void)
{
	// Tests for examples that should passed
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
		if (result == NULL)
		{
			printf("Out of memory error during testing\n");
			return testOutOfMemoryError;
		}
		ErrorCode errorCode = infixToPostfix(testExpressions[i], result);
		if (strcmp(result, expectedResults[i]) == 0)
		{
			printf("Test %d failed\n", i + 1);
			free(result);
			return testFailed;
		}
	}

	// Tests to check error codes
	char testExpressionsForErrorCodes[][100] = { "((1 + 1)",
												"(2 / 3))",
												"asfiu",
												"(a + b)",
												"(5 + 4) / 3" };
	ErrorCode expectedResultsForErrorCodeTests[] = { openedParanthesesError, closedParanthesesError, inputExpressionError, inputExpressionError, ok };

	for (int i = 0; i < 5; ++i)
	{
		char* temp = malloc(sizeof(char) * 100);
		if (temp == NULL)
		{
			printf("Out of memory error during testing\n");
			return testOutOfMemoryError;
		}
		ErrorCode errorCode = infixToPostfix(testExpressionsForErrorCodes[i], temp);
		if (errorCode != expectedResultsForErrorCodeTests[i])
		{
			free(temp);
			printf("Test for error code working %d failed\n", i + 1);
			return testFailed;
		}
	}
	return testsPassed;
}