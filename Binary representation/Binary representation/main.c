#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>

int writeData(int* number1, int* number2)
{
    int amountOfValues;
    char check;

    printf("Введите первое число: ");
    amountOfValues = scanf_s("%d%c", number1, &check);
    if (amountOfValues != 2 || check != '\n')
    {
        printf("Некорректный ввод данных\n");
        return 1;
    }

    printf("Введите второе число: ");
    amountOfValues = scanf_s("%d%c", number2, &check);
    if (amountOfValues != 2 || check != '\n')
    {
        printf("Некорректный ввод данных\n");
        return 2;
    }
    printf("\n");
    return 0;
}

void showBinaryRepresentation(int numberOfDigits, int* binaryNumber)
{
    for (int i = 0; i < numberOfDigits; ++i)
    {
        printf("%d", binaryNumber[i]);
    }
    printf("\n");
}

void convertToBinary(int number, int* binaryNumber, int numberOfDigits)
{
    // переводим число в двоичную систему счисления
    int i = numberOfDigits - 1;

    // выводим надпись, чтобы number сохранило свое значение перед сбросом до нуля
    printf("число %d в двоичной системе счисления выглядит так: ", number);
    while (number > 0)
    {
        binaryNumber[i] = number % 2;
        number /= 2;
        i--;
    }

    showBinaryRepresentation(numberOfDigits, binaryNumber);
}

int main(void)
{
    setlocale(LC_ALL, "Rus");
    int number1, number2;

    const int errorWriteData = writeData(&number1, &number2);
    if (!errorWriteData)
    {
        // создаем массивы, длина которых равна количеству разрядов в их двоичном виде
        int numberOfDigits1 = (int)log2(number1) + 1;
        int numberOfDigits2 = (int)log2(number2) + 1;
        int* binaryNumber1 = (int*)calloc(numberOfDigits1, sizeof(int));
        int* binaryNumber2 = (int*)calloc(numberOfDigits1, sizeof(int));

        convertToBinary(number1, binaryNumber1, numberOfDigits1);
        convertToBinary(number2, binaryNumber2, numberOfDigits2);

        free(binaryNumber1);
        free(binaryNumber2);
        return 0;
    }
    return errorWriteData;
}