#include <stdlib.h>
#include <stdio.h>

#include "parseTree.h"
#include "tests.h"

#define MAX_LENGTH_OF_TEST_FILE_NAME 10
#define NUMBER_OF_TESTS 6

bool runTests(void)
{
    const char testFilesNames[NUMBER_OF_TESTS][MAX_LENGTH_OF_TEST_FILE_NAME] = { "test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt", "test6.txt" };
    const int expectedCalculations[NUMBER_OF_TESTS] = { 8, 126, -75, 128, divisionByZero, 2 };
    const int expectedErrorCodes[NUMBER_OF_TESTS] = { okParseTree, okParseTree, okParseTree, okParseTree, divisionByZero, okParseTree };

    for (size_t i = 0; i < NUMBER_OF_TESTS; ++i)
    {
        ParseTree* testTree = createParseTree();
        const ParseTreeError errorBuild = buildParseTree(&testTree, testFilesNames[i]);
        if (errorBuild)
        {
            clearParseTree(&testTree);
            printf("Out of memory during tests\n");
            return false;
        }

        ParseTreeError errorCode = okParseTree;
        const int result = calculateParseTree(testTree, &errorCode);
        clearParseTree(&testTree);
        if (result != expectedCalculations[i] || errorCode != expectedErrorCodes[i])
        {
            printf("%d\n", result);
            printf("Test %Iu doesn't passed\n", i + 1);
            return false;
        }
    }
    return true;
}