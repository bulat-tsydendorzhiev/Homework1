#include <stdio.h>

#include "BinarySearchTree.h"
#include "tests.h"
#include "commands.h"

int main()
{
    system("chcp 1251 > nul");

    TestErrorCode testError = tests();
    if (testError)
    {
        return testError;
    }

    comandError error = commands();
    if (error)
    {
        printf("Произошла ошибка\n");
        return error;
    }
    return 0;
}