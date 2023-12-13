#include <stdio.h>
#include <stdbool.h>

typedef enum
{
    testFailed = -1,
    ok,
    scanError
} ErrorCode;

bool tests(void)
{


    return true;
}

int main()
{
    const bool testPassed = tests();
    if (!testPassed)
    {
        return testFailed;
    }

    int number = 0;
    printf("Введите натуральное число: ");
    if (scanf_s("%d", &number) != 1 || number <= 0)
    {
        return scanError;
    }

    int num = 321;


    return ok;
}