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

    printf("число %d двоичном виде выглядит вот так: ", number);
    for (int i = 0; i < 32; ++i)
    {
        printf("%d", binary[i]);
    }
    printf("\n");
}

void convertBinaryToDecimal(int* binary) {
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

    printf("%d\n", decimal);
}

void addBinaryColumn(int* binary1, int* binary2)
{
    int carry = 0; // Перенос
    int result[32]; // Результат

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

    // Выводим результат в двоичном и десятичном видах
    printf("Результат сложения в двоичном виде: ");
    for (int i = 0; i < 32; i++) {
        printf("%d", result[i]);
    }
    printf("\n");

    printf("Результат сложения в десятичном виде: ");
    convertBinaryToDecimal(result);
}

int main(void)
{
    setlocale(LC_ALL, "Rus");
    int number1, number2;

    const int errorWirteData = writeData(&number1, &number2);
    if (!errorWirteData) // защита от дурака
    {
        int binary1[32], binary2[32];
        convertDecimalToBinary(number1, binary1);
        convertDecimalToBinary(number2, binary2);

        addBinaryColumn(binary1, binary2);
        return 0;
    }
    return errorWirteData;
}