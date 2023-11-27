#include <stdio.h>

#include "tests.h"
#include "console.h"

int main()
{
    system("chcp 1251 > nul");
    const bool testError = tests();
    if (testError)
    {
        printf("Tests had failed\n");
        return testError;
    }

    ConsoleError error = console();
    if (error)
    {
        printf("Error occured\n");
    }

    return 0;
}