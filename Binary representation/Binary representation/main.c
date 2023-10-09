#include <stdio.h>
#include <locale.h>

int writeData(int* number1, int* number2)
{
    int amountOfValues;
    char check;

    printf("Введите первое десятичное число: ");
    amountOfValues = scanf_s("%d%c", number1, &check);
    if (amountOfValues != 2 || check != '\n')
    {
        printf("Некорректный ввод данных\n");
        return 1;
    }

    printf("Введите второе десятичное число: ");
    amountOfValues = scanf_s("%d%c", number2, &check);
    if (amountOfValues != 2 || check != '\n')
    {
        printf("Некорректный ввод данных\n");
        return 2;
    }
    printf("\n");
    return 0;
}

void convertDecimalToBinary(int number, int* binary)
{
    int i = 0;
    while (i < 32)
    {
        binary[31 - i] = (number >> i) & 1; // Получение i-го бита числа
        i++;
    }
}

int convertBinaryToDecimal(int* binary) {
    int decimal = 0; // Искомое число
    int i = 32;
    int power = 1; // Степень двойки

    // Если число отрицательное, устанавливаем старший бит в 1
    if (binary[i] == 1) {
        decimal = -power;
    }

    i--;

    while (i >= 0) {
        decimal += binary[i] * power;
        power *= 2;
        i--;
    }

    return decimal;
}

void addBinaryColumn(int* binary1, int* binary2, int* result)
{
    int carry = 0; // Перенос

    // Складываем числа по разрядам
    for (int i = 31; i >= 0; i--) {
        int bit1 = binary1[i]; // Получаем текущий бит первого числа
        int bit2 = binary2[i]; // Получаем текущий бит второго числа

        // Складываем биты с учетом переноса
        int sum = bit1 ^ bit2 ^ carry;

        // Обновляем перенос
        carry = (bit1 & bit2) | (bit1 & carry) | (bit2 & carry);

        // Сохраняем результат в обратном порядке
        result[i] = sum;
    }
}

void printBinary(int* binary)
{
    // Выводит двоичную запись
    for (int i = 0; i < 32; i++) {
        printf("%d", binary[i]);
    }
    printf("\n");
}

void printAnswer(int number1, int number2)
{
    // Заводим 2 массива для хранения двоичной записи и один для хранения результата сложения в столбик
    int binary1[32], binary2[32], resultOfSumm[32];

    // Переводим числа в их двоичную запись выводим их в консоль
    printf("Число %d двоичном виде выглядит вот так: ", number1);
    convertDecimalToBinary(number1, binary1);
    printBinary(binary1);

    printf("Число %d двоичном виде выглядит вот так: ", number2);
    convertDecimalToBinary(number2, binary2);
    printBinary(binary2);

    // Выполняем сложение в столбик и выводим на экран результат в двоичном и десятичном видах
    addBinaryColumn(binary1, binary2, resultOfSumm);
    printf("Результат сложения в двоичном виде: ");
    printBinary(resultOfSumm);

    const int decimalNotation = convertBinaryToDecimal(resultOfSumm);
    printf("Результат сложения в десятичной записи: %d\n", decimalNotation);
}

int tests(void)
{
    // Тест 1: сумма положительных чисел
    int number11 = 5, number12 = 7, binary11[32], binary12[32], resultOfSumm1[32];

    convertDecimalToBinary(number11, binary11);
    convertDecimalToBinary(number12, binary12);
    addBinaryColumn(binary11, binary12, resultOfSumm1);
    const int decimalNotation1 = convertBinaryToDecimal(resultOfSumm1);

    if (decimalNotation1 != 12)
    {
        return 21;
    }

    // Тест 2: сумма отрицательных чисел
    int number21 = -5, number22 = -7, binary21[32], binary22[32], resultOfSumm2[32];

    convertDecimalToBinary(number21, binary21);
    convertDecimalToBinary(number22, binary22);
    addBinaryColumn(binary21, binary22, resultOfSumm2);
    const int decimalNotation2 = convertBinaryToDecimal(resultOfSumm2);

    if (decimalNotation2 != -12)
    {
        return 22;
    }

    // Тест 3: сумма отрицательного и положительного чисел
    int number31 = -5, number32 = 7, binary31[32], binary32[32], resultOfSumm3[32];

    convertDecimalToBinary(number31, binary31);
    convertDecimalToBinary(number32, binary32);
    addBinaryColumn(binary31, binary32, resultOfSumm3);
    const int decimalNotation3 = convertBinaryToDecimal(resultOfSumm3);

    if (decimalNotation3 != 2)
    {
        return 23;
    }

    // Тест 4: сумма c числом, являющимся нулем
    int number41 = 0, number42 = 7, binary41[32], binary42[32], resultOfSumm4[32];

    convertDecimalToBinary(number41, binary41);
    convertDecimalToBinary(number42, binary42);
    addBinaryColumn(binary41, binary42, resultOfSumm4);
    const int decimalNotation4 = convertBinaryToDecimal(resultOfSumm4);

    if (decimalNotation4 != 7)
    {
        return 24;
    }
    return 0;
}

int main(void)
{
    setlocale(LC_ALL, "Rus");
    int number1, number2;
    const int errorTest = tests();
    if (!errorTest)
    {
        const int errorWirteData = writeData(&number1, &number2);
        if (!errorWirteData) // защита от дурака
        {
            printAnswer(number1, number2);
            return 0;
        }
        return errorWirteData;
    }
    return errorTest;
}