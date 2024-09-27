#include <stdio.h>
#include <stdbool.h>

typedef unsigned int number;

typedef enum
{
    success,
    testsFailed = -1
} ErrorCode;

number convertBinaryToDecimal(const bool* const binaryNumber, const number length)
{
    number result = 0;
    number power = 1;
    for (number i = 0; i < length; ++i)
    {
        if (binaryNumber[length - i - 1])
        {
            result += power;
        }
        power = power << 1;
    }
    return result;
}

bool tests(void)
{
    const bool greaterNumbers[][10] = { { true, false, true}, {true, true, true}, {true, true, true, true, true} };
    const bool lessNumbers[][10] = { { false }, {false, true, true}, {false, false, false, false, false} };
    const number lengths[][2] = { {3, 1}, {3, 3}, {5,5} };
    for (size_t i = 0; i < 2; ++i)
    {
        const number greaterNumber = convertBinaryToDecimal(greaterNumbers, lengths[i][0]);
        const number lessNumber = convertBinaryToDecimal(lessNumbers, lengths[i][1]);
        if (greaterNumber < lessNumber)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    const bool testsPassed = tests();
    if (!testsPassed)
    {
        return testsFailed;
    }
    const bool binaryNumber1[] = { true, false, true };
    const bool binaryNumber2[] = { true, true, true };
    const number numberOfDigits1 = sizeof(binaryNumber1) / sizeof(binaryNumber1[0]);
    const number numberOfDigits2 = sizeof(binaryNumber2) / sizeof(binaryNumber2[0]);
    
    const number number1 = convertBinaryToDecimal(binaryNumber1, numberOfDigits1);
    const number number2 = convertBinaryToDecimal(binaryNumber2, numberOfDigits2);

    if (number1 > number2)
    {
        printf("The first number is greater than second\n");
    }
    else if (number1 == number2)
    {
        printf("Numbers are equal");
    }
    else
    {
        printf("The second number is greater than first\n");
    }
    
    return 0;
}