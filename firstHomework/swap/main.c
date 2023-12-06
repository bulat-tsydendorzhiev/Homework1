#include <stdio.h>

void swap(int* number1, int* number2)
{
    *number1 ^= *number2;
    *number2 ^= *number1;
    *number1 ^= *number2;
}

int main()
{
    int number1 = 0, number2 = 0;
    printf("Enter two integer numbers\n");

    printf("First number: ");
    scanf_s("%d", &number1);
    printf("Second number: ");
    scanf_s("%d", &number2);

    printf("*Swap*\n");
    swap(&number1, &number2);

    printf("Now first number = %d, second number = %d\n", number1, number2);
    return 0;
}