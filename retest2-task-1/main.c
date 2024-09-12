#include <stdio.h>
#include <stdlib.h>

#include "tests.h"

#define OK 0
#define TESTS_FAILED -1

int main()
{
    const bool testsPassed = runTests();
    if (!testsPassed)
    {
        return TESTS_FAILED;
    }
    return OK;
}