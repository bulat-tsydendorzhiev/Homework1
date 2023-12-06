#include <stdio.h>

#include "tests.h"
#include "console.h"

int main()
{
    const bool testError = tests();
    if (testError)
    {
        return testError;
    }

    const int errorOccured = console();
    if (errorOccured)
    {
        printf("Error occurred\n");
        return errorOccured;
    }

    return 0;
}