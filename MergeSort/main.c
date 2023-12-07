#include <stdio.h>

#include "tests.h"
#include "console.h"

int main()
{
    const bool testsPassed = tests();
    if (!testsPassed)
    {
        return !testsPassed;
    }
    return runProgram();
}