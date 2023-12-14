#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "console.h"
#include "tests.h"
#include "substringSearch.h"

int main()
{
    const bool testsPassed = tests();
    if (!testsPassed)
    {
        return -1;
    }
    return runProgram();
}