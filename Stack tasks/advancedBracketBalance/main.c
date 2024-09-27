#include <stdio.h>

#include "advancedBracketBalance.h"
#include "tests.h"

#define MAX_STRING_LENGTH 100

typedef enum
{
    testsFailed = -1,
    success,
    scanError
};

int main(void)
{
    const bool testsPassed = runTests();
    if (!testsPassed)
    {
        return testsFailed;
    }

    char string[MAX_STRING_LENGTH] = "";
    printf("Enter string: ");
    if (scanf_s("%s", string, MAX_STRING_LENGTH) != 1)
    {
        return scanError;
    }

    printf(isBalanced(string) ? "String is balanced\n": "String is not balanced\n");

    return success;
}