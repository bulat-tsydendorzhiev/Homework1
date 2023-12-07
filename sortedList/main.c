#include <stdio.h>
#include <stdbool.h>

#include "tests.h"
#include "console.h"

int main()
{
    const bool testPassed = tests();
    if (!testPassed)
    {
        return !testPassed;
    }
    return runProgram();
}