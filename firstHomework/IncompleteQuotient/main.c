#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef enum
{
    divisionByZero = -2,
    success = 0,
    scanError
} ErrorCode;

int countIncompleteQuotient(int dividend, int divisor)
{
    int quotient = 0;
    const int sign = dividend < 0 ^ divisor < 0 ? -1 : 1;
    const bool negativeDividend = dividend < 0;
    if (negativeDividend)
    {
        ++quotient;
    }

    dividend = abs(dividend);
    divisor = abs(divisor);
    while (dividend - divisor >= 0)
    {
        dividend -= divisor;
        ++quotient;
    }

    if (dividend == 0 && negativeDividend)
    {
        --quotient;
    }

    return sign * quotient;
}

int main()
{
    int dividend = 0;
    int divisor = 0;

    printf("Enter dividend: ");
    if (scanf_s("%d", &dividend) != 1)
    {
        printf("Input error\n");
        return scanError;
    }
    printf("Enter divisor: ");
    if (scanf_s("%d", &divisor) != 1)
    {
        printf("Input error\n");
        return scanError;
    }
    if (divisor == 0)
    {
        printf("Division by zero\n");
        return divisionByZero;
    }

    printf("Quotient = %d\n", countIncompleteQuotient(dividend, divisor));
    return success;
}
