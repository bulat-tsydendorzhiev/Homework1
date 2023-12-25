#include <stdio.h>

#include "tests.h"
#include "console.h"

int main()
{
    const bool testsPassed = runTests();
    if (!testsPassed)
    {
        return !testsPassed;
    }
    return runProgram();
}