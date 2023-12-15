#include <stdbool.h>
#include <stdio.h>

#include "console.h"
#include "tests.h"

#define TESTS_FAILED -1

int main()
{
    const bool testsPassed = runTests();
    if (!testsPassed)
    {
        return TESTS_FAILED;
    }
    return runProgram();
}