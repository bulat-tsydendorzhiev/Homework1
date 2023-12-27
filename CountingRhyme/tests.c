#include <stdlib.h>
#include <stdio.h>

#include "tests.h"
#include "countingRhyme.h"

static void printTestsResults(bool* const testsResults, bool* const finalResult)
{
    for (size_t i = 0; i < 5; ++i)
    {
        printf(testsResults[i] ? "Test %d passed\n" : "Test %d failed\n", i + 1);
        if (!testsResults[i])
        {
            *finalResult = false;
        }
    }
}

static void executeTestsForCounting(bool* const testsResults)
{
    const bool testCases[][3] = { {5, 2, 3},
                             {10, 3, 4},
                             {15, 1, 15},
                             {1, 6, 1},
                             {25, 4, 15} };
    const int numberOfTests = sizeof(testCases) / sizeof(testCases[0]);

    for (size_t i = 0; i < numberOfTests; ++i)
    {
        const int numberOfWarriors = testCases[i][0];
        const int needTokillEvery = testCases[i][1];
        const int expectedResult = testCases[i][2];

        const int result = countPositionOfLastWarrior(numberOfWarriors, needTokillEvery);
        testsResults[i] = (result == expectedResult);
    }
}

bool tests(void)
{
    bool* testsResults = (bool*)calloc(5, sizeof(bool));
    if (testsResults == NULL)
    {
        printf("Out of memory error\n");
        return false;
    }

    executeTestsForCounting(testsResults);
    bool finalResult = true;
    printTestsResults(testsResults, &finalResult);
    
    free(testsResults);
    return finalResult;
}
