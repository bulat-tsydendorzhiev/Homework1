#include "tests.h"
#include "console.h"

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