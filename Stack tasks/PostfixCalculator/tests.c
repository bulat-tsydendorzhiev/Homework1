#include <stdio.h>

#include "tests.h"
#include "postfixCalculator.h"

#define MAX_LENGTH_OF_TEST_EXPRESSION 14
#define NUMBER_OF_TESTS 4

bool runTests(void)
{
    const char testExpressions[NUMBER_OF_TESTS][MAX_LENGTH_OF_TEST_EXPRESSION] = { "3 5 +", "5 2 3 * +", "8 4 2 / 5 * +", "2 5 -" };
    const int expectedResults[NUMBER_OF_TESTS] = { 8, 11, 18, -3 };
    for (size_t i = 0; i < NUMBER_OF_TESTS; ++i)
    {
        ErrorCode errorCode = ok;
        const int testExpressionResult = calculatePostfixArithmeticExpression(testExpressions[i], &errorCode);
        if (testExpressionResult != expectedResults[i] || errorCode)
        {
            printf("Test %Iu failed\n", i + 1);
            return false;
        }
    }
    return true;
}