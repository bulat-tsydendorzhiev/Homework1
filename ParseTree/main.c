#include <stdio.h>

#include "parseTree.h"
#include "tests.h"

#define TESTS_FAILED -1

int main()
{
    const bool testsPassed = runTests();
    if (!testsPassed)
    {
        printf("Tests failed\n");
        return TESTS_FAILED;
    }

    ParseTree* parseTree = createParseTree();
    if (parseTree == NULL)
    {
        return outOfMemoryParseTree;
    }

    const ParseTreeError errorBuild = buildParseTree(&parseTree, "mainFile.txt");
    if (errorBuild)
    {
        printf("Error occurred during building parse tree\n");
        clearParseTree(&parseTree);
        return errorBuild;
    }

    ParseTreeError errorCode = okParseTree;
    const int resultOfCalculations = calculateParseTree(parseTree, &errorCode);
    if (errorCode)
    {
        clearParseTree(&parseTree);
        return errorCode;
    }

    printParseTree(parseTree);
    printf(" = %d\n", resultOfCalculations);

    clearParseTree(&parseTree);
    return 0;
}