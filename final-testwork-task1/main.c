#include <stdio.h>
#include <stdbool.h>

#include "dataInit.h"
#include "algorithm.h"

typedef enum
{
    testFailed = -1,
    ok,
    scanError,
    outOfMemory
} ErrorCode;

bool check(const char* const number, const size_t length)
{
    for (size_t i = 1; i < length; i++)
    {
        if (number[i - 1] > number[i])
        {
            return false;
        }
    }
    return true;
}

bool tests(void)
{
    char testCases[][20] = { "312", "1329", "16", "1"};
    const size_t lengths[] = {3, 4, 2, 1};

    for (size_t i = 0; i < 4; i++)
    {
        const size_t length = lengths[i];
        const char* minNumber = getMinNumber(testCases[i], length);
        if (!check(minNumber, length))
        {
            printf("%s\n", minNumber);
            free(minNumber);
            return false;
        }
        free(minNumber);
    }
    return true;
}

int main()
{
    const bool testPassed = tests();
    if (!testPassed)
    {
        return testFailed;
    }

    printf("Enter natural number: ");
    size_t length = 0;
    char* number = getString(&length);
    if (number == NULL)
    {
        printf("Lack of memory error\n");
        return outOfMemory;
    }
    if (number[0] == '-')
    {
        printf("Number must be NATURAL\n");
        return scanError;
    }

    char* minNumber = getMinNumber(number, length);
    if (minNumber == NULL)
    {
        free(number);
        printf("Lack of memory error\n");
        return outOfMemory;
    }

    printf("minimal number from number is %s", minNumber);

    free(number);
    free(minNumber);
    return ok;
}