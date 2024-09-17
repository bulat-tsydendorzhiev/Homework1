#include <locale.h>

#include "console.h"
#include "tests.h"

#define TESTS_FAILED -1

int main()
{
    setlocale(LC_ALL, "Rus");

    const bool testsPassed = runTests();
    if (!testsPassed)
    {
        return TESTS_FAILED;
    }

    return runProgram();
}