#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tests.h"
#include "shuntingYard.h"

bool runTests(void)
{
    // Tests for examples that should passed
    char testExpressions[][MAX_STRING_LENGTH] = { "3 + 2",
                                "3 + 4 + 2 + 1",
                                "3 + 4 * 2 / ( 1 - 5 )",
                                "( 3 + 4 ) * ( 2 - 1 )" };
    char expectedResults[][MAX_STRING_LENGTH] = { "3 2 +",
                                "3 4 + 2 + 1 +",
                                "3 4 2 * 1 5 - / +",
                                "3 4 + 2 1 - *" };
    for (size_t i = 0; i < 5; ++i)
    {
        char result[MAX_STRING_LENGTH] = "";
        ErrorCode errorCode = translateInfixToPostfix(testExpressions[i], result);
        if (strcmp(result, expectedResults[i]) == 0)
        {
            printf("Test %Iu failed\n", i + 1);
            return false;;
        }
    }

    // Tests to check error codes
    char testExpressionsForErrorCodes[][100] = { "((1 + 1)",
                                                "(2 / 3))",
                                                "asfiu",
                                                "(a + b)",
                                                "(5 + 4) / 3" };
    ErrorCode expectedResultsForErrorCodeTests[] = { openedParenthesesError, closedParenthesesError, inputExpressionError, inputExpressionError, ok };
    for (size_t i = 0; i < 5; ++i)
    {
        char result[MAX_STRING_LENGTH] = "";
        ErrorCode errorCode = translateInfixToPostfix(testExpressionsForErrorCodes[i], result);
        if (errorCode != expectedResultsForErrorCodeTests[i])
        {
            printf("Test for error code working %Iu failed\n", i + 1);
            return false;
        }
    }

    return true;
}