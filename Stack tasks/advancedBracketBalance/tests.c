#include <stdio.h>

#include "tests.h"
#include "advancedBracketBalance.h"

bool runTests(void)
{
    const char tests[][5] = { "90", "(())", "({})","({)}", "(){}" };
    const bool expectedResults[] = { true, true, true, false, true };
    for (size_t i = 0; i < 5; ++i)
    {
        if (isBalanced(tests[i]) != expectedResults[i])
        {
            return false;
        }
    }
    return true;
}