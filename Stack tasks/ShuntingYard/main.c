#include <stdio.h>
#include <stdlib.h>

#include "tests.h"
#include "console.h"

#define TESTS_FAILED -1

int main(void)
{
    const bool testsPassed = runTests();
    if (!testsPassed)
    {
        return TESTS_FAILED;
    }

    return runProgram();
}