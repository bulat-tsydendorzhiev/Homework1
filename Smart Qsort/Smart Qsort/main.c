#include <stdio.h>
#include <stdlib.h>

#include "tests.h"
#include "smartQsort.h"
#include "console.h"

int main(void)
{
    const bool testsPassed = tests();
    if (!testsPassed)
    {
        return -1;
    }
    return runProgram();
}
