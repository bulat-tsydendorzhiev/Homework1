#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#define BINARY_REPRESENTATION_SIZE (sizeof(int) * 8)

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

ErrorCode initData(int* const number1, int* const number2)
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

void convertDecimalToBinary(const int number, int binaryNumber[BINARY_REPRESENTATION_SIZE])
{
    for (size_t i = 0; i < BINARY_REPRESENTATION_SIZE; ++i)
    {
        binaryNumber[BINARY_REPRESENTATION_SIZE - i - 1] = (number >> i) & 1;
    }
}

int convertBinaryToDecimal(const int binaryNumber[BINARY_REPRESENTATION_SIZE])
{
    int decimal = 0;
    for (size_t i = 0; i < BINARY_REPRESENTATION_SIZE; ++i)
    {
        decimal += binaryNumber[i] << (BINARY_REPRESENTATION_SIZE - i - 1);
    }
    return decimal;
}

void sumTwoBinaryNumbersInColumn(const int binaryNumber1[BINARY_REPRESENTATION_SIZE], const int binaryNumber2[BINARY_REPRESENTATION_SIZE], int result[BINARY_REPRESENTATION_SIZE])
{
    int carry = 0;

    for (int i = BINARY_REPRESENTATION_SIZE - 1; i >= 0; --i)
    {
        const int bit1 = binaryNumber1[i];
        const int bit2 = binaryNumber2[i];
        const int sum = bit1 ^ bit2 ^ carry;

        carry = (bit1 & bit2) | (bit1 & carry) | (bit2 & carry);
        result[i] = sum;
    }
}

void printBinaryNumber(const int binaryNumber[BINARY_REPRESENTATION_SIZE])
{
    for (size_t i = 0; i < BINARY_REPRESENTATION_SIZE; ++i)
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
        int binaryNumber1[BINARY_REPRESENTATION_SIZE] = { 0 };
        int binaryNumber2[BINARY_REPRESENTATION_SIZE] = { 0 };
        int resultOfSum[BINARY_REPRESENTATION_SIZE] = { 0 };
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
    const ErrorCode errorInit = initData(&number1, &number2);
    if (errorInit)
    {
        return errorInit;
    }

    int binaryNumber1[BINARY_REPRESENTATION_SIZE] = { 0 };
    int binaryNumber2[BINARY_REPRESENTATION_SIZE] = { 0 };
    int resultOfSum[BINARY_REPRESENTATION_SIZE] = { 0 };
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