#include <stdio.h>

#include "AVLTree.h"
#include "AVLTreeTests.h"
#include "commandsAVLTree.h"

int main()
{
    system("chcp 1251 > nul");

    const AVLTreeTestErrorCode errorTest = testsAVLTree();
    if (errorTest)
    {
        return errorTest;
    }

    const CommandError commandError = commands();
    if (commandError)
    {
        return commandError;
    }

    return 0;
}