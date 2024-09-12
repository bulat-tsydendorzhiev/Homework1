#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool isPrimeNumber(const int number)
{
    for (size_t i = 2; i <= pow(number, 0.5); ++i)
    {
        if (number % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int number = 0;
    printf("Enter number: ");
    if (scanf_s("%d", &number) != 1 || number < 0)
    {
        printf("Error input\n");
        return 1;
    }

    printf("Prime numbers do not exceeding %d: ", number);
    for (size_t i = 2; i <= number; ++i)
    {
        if (isPrimeNumber(i))
        {
            printf("%Iu ", i);
        }
    }
    printf("\n");
    return 0;
}