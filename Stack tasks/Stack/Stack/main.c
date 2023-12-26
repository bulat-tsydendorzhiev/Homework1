#include <stdio.h>

#include "IntStack.h"
#include "CharStack.h"
#include "StackTests.h"

#define SUCCESS 0
#define TESTS_FAILED -1

int main(void)
{
    const bool testsPassed = runTests();
    if (!testsPassed)
    {
        return TESTS_FAILED;
    }
    
    printf("Tests passed succesfully!\n");
    return SUCCESS;
}