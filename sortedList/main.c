#include <stdio.h>
#include <stdbool.h>

#include "tests.h"
#include "console.h"

#include "sortedList.h"

int main()
{
    const bool testPassed = tests();
    if (!testPassed)
    {
        return !testPassed;
    }
    return runProgram();
}