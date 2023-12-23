#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

typedef enum
{
    testsFailed = -1,
    success,
    scanError
} ErrorCode;

bool readNumber(int* const number, const char* const indexNumber)
{
    printf("Введите %s число: ", indexNumber);
    return scanf_s("%d", number) == 1;
}

int initData(int* const number1, int* const number2)
{
    if (!readNumber(number1, "первое"))
    {
        return scanError;
    }
    if (!readNumber(number2, "второе"))
    {
        return scanError;
    }
    return success;
}

void convertDecimalToBinary(const int number, int binaryNumber[32])
{
    size_t i = 0;
    while (i < 32)
    {
        binaryNumber[31 - i] = (number >> i) & 1;
        ++i;
    }
}

int convertBinaryToDecimal(const int binaryNumber[32])
{
    int decimal = 0;
    int power = 1;

    if (binaryNumber[32] == 1)
    {
        decimal = -power;
    }

    int i = 31;
    while (i >= 0)
    {
        decimal += binaryNumber[i] * power;
        power = power << 1;
        --i;
    }

    return decimal;
}

void sumTwoBinaryNumbersInColumn(const int binaryNumber1[32], const int binaryNumber2[32], int result[32])
{
    int carry = 0;

    for (int i = 31; i >= 0; --i)
    {
        const int bit1 = binaryNumber1[i];
        const int bit2 = binaryNumber2[i];
        const int sum = bit1 ^ bit2 ^ carry;

        carry = (bit1 & bit2) | (bit1 & carry) | (bit2 & carry);
        result[i] = sum;
    }
}

void printBinaryNumber(const int binaryNumber[32])
{
    for (size_t i = 0; i < 32; ++i)
    {
        printf("%d", binaryNumber[i]);
    }
    printf("\n");
}

bool runTests(void)
{
    const int testCases[][3] = { {4, 6, 10}, {-5, -7, -12}, {-5, 0, -5}, {5, -2, 3} };
    for (size_t i = 0; i < 4; ++i)
    {
        int binaryNumber1[32] = { 0 };
        int binaryNumber2[32] = { 0 };
        int resultOfSum[32] = { 0 };
        convertDecimalToBinary(testCases[i][0], binaryNumber1);
        convertDecimalToBinary(testCases[i][1], binaryNumber2);
        sumTwoBinaryNumbersInColumn(binaryNumber1, binaryNumber2, resultOfSum);
        if (convertBinaryToDecimal(resultOfSum) != testCases[i][2])
        {
            printf("Тест %Iu провалился\n", i + 1);
            return false;
        }
    }
    return true;
}

int main(void)
{
    setlocale(LC_ALL, "Rus");

    const bool testsPassed = runTests();
    if (!testsPassed)
    {
        return testsFailed;
    }

    int number1 = 0;
    int number2 = 0;
    const int errorInit = initData(&number1, &number2);
    if (errorInit)
    {
        return errorInit;
    }

    int binaryNumber1[32] = { 0 };
    int binaryNumber2[32] = { 0 };
    int resultOfSum[32] = { 0 };
    convertDecimalToBinary(number1, binaryNumber1);
    convertDecimalToBinary(number2, binaryNumber2);

    printf("Двоичное представление числа %d: ", number1);
    printBinaryNumber(binaryNumber1);

    printf("Двоичное представление числа %d: ", number2);
    printBinaryNumber(binaryNumber2);

    sumTwoBinaryNumbersInColumn(binaryNumber1, binaryNumber2, resultOfSum);
    printf("Результат сложения чисел в их двоичном представлении: ");
    printBinaryNumber(resultOfSum);
    printf("Результат сложения чисел в десятичной системе счисления: %d", convertBinaryToDecimal(resultOfSum));

    return success;
}