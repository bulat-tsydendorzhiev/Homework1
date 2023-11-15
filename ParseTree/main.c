#include <stdio.h>

#include "parseTree.h"
#include "tests.h"

int main()
{
    system("chcp 1251 > nul");
    const TestErrorCode testError = tests();
    if (testError)
    {
        return testError;
    }

    ParseTree* parseTree = createParseTree();
    ParseTreeError errorBuild = buildParseTree(&parseTree, "mainFile.txt");
    if (errorBuild)
    {
        return errorBuild;
    }

    ParseTreeError errorCode = okParseTree;
    const int resultOfCalculations = calculateParseTree(parseTree, &errorCode);
    if (errorCode)
    {
        printf("Division by zero\n");
        return errorCode;
    }

    printParseTree(parseTree);
    printf(" = %d\n", resultOfCalculations);
    clearParseTree(&parseTree);
    return 0;
}