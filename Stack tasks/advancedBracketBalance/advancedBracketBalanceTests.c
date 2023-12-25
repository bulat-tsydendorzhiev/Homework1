#include <stdio.h>

#include "advancedBracketBalanceTests.h"
#include "advancedBracketBalance.h"

TestErrorCode tests(void)
{
    char tests[][5] = { "90", "(())", "({})","({)}", "{(){}" };
    BalanceError resultOfTests[] = { balance, balance, balance, balance, balance };
    BalanceError expectedresults[] = { balance, balance, balance, stackError, stackError };

    for (int i = 0; i < 5; ++i)
    {
        isBalanced(tests[i], &resultOfTests[i]);
        if (resultOfTests[i] != expectedresults[i])
        {
            printf("Test %d didn't passed\n", i + 1);
            return testFailed;
        }
    }
    return testsPassed;
}