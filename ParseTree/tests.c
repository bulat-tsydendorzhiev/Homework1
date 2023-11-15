#include <stdlib.h>
#include <stdio.h>

#include "parseTree.h"
#include "tests.h"

TestErrorCode tests(void)
{
    const char testFilesNames[][10] = { "test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt" };
    const int expectedCalculations[] = { 8, 126, -75, 128, -1 };
    const int expectedErrorCodes[] = { okParseTree, okParseTree, okParseTree, okParseTree, divisionByZero };

    const size_t numberOfTests = sizeof(testFilesNames) / sizeof(testFilesNames[0]);

    for (size_t i = 0; i < numberOfTests; ++i)
    {
        ParseTree* testTree = createParseTree();
        const ParseTreeError errorBuild = buildParseTree(&testTree, testFilesNames[i]);
        if (errorBuild)
        {
            printf("Out of memory during tests\n");
            return buildingError;
        }

        ParseTreeError errorCode = okParseTree;
        const int result = calculateParseTree(testTree, &errorCode);
        if (result != expectedCalculations[i] || errorCode != expectedErrorCodes[i])
        {
            printf("Test %d doesn't passed\n", (int)i + 1);
            clearParseTree(&testTree);
            return testFailed;
        }
        clearParseTree(&testTree);
    }
    return testsPassed;
}