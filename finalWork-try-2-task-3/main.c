#include <stdio.h>
#include <stdlib.h>

#include "tests.h"
#include "stateMachine.h"
#include "dataInit.h"

typedef enum
{
    testsFailed = -1,
    success,
    outOfMemory = 2
} ErrorCode;

int main()
{
    const bool testsPassed = runTests();
    if (!testsPassed)
    {
        return testsFailed;
    }

    printf("Enter string: ");
    char* string = getString();
    if (string == NULL)
    {
        return outOfMemory;
    }

    printf(isRightString(string) ? "String matches regular expression\n": "String doesn't match regular expression\n");

    free(string);
    return success;
}