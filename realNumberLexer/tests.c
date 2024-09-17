#include <stdlib.h>
#include <stdio.h>

#include "tests.h"
#include "realNumberLexer.h"

#define MAX_LENGTH_OF_TEST_STRING 30
#define NUMBER_OF_TESTS_WITH_CORRECT_CASES 4
#define NUMBER_OF_TESTS_WITH_UNCORRECT_CASES 4

bool runTests(void)
{
    const char correctTestCases[NUMBER_OF_TESTS_WITH_CORRECT_CASES][MAX_LENGTH_OF_TEST_STRING] = { "123", "45.6", "3.14159E-20", "6.022E+23" };
    for (size_t i = 0; i < NUMBER_OF_TESTS_WITH_CORRECT_CASES; ++i)
    {
        if (!isRealNumber(correctTestCases[i]))
        {
            printf("Test %Iu with correct cases failed\n", i + 1);
            return false;
        }
    }

    const char uncorrectTestCases[NUMBER_OF_TESTS_WITH_UNCORRECT_CASES][MAX_LENGTH_OF_TEST_STRING] = { "i am not real number", "123e", "456E", "-123"};
    for (size_t i = 0; i < NUMBER_OF_TESTS_WITH_UNCORRECT_CASES; ++i)
    {
        if (isRealNumber(uncorrectTestCases[i]))
        {
            printf("Test %Iu with correct cases failed\n", i + 1);
            return false;
        }
    }
    return true;
}