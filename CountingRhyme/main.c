#include <stdio.h>
#include <stdbool.h>

#include "tests.h"
#include "console.h"

int main(void)
{
    const bool testsPassed = tests();
    if (!testsPassed)
    {
        return !testsPassed;
    }
    return runProgram();
}
