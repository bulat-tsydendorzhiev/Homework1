#include <stdio.h>
#include <locale.h>

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
    return 0;
}

int tests(void)
{
    // здесь будут тесты
}

int main(void)
{
    setlocale(LC_ALL,"Rus");
    int number1, number2;

    const int errorWriteData = writeData(&number1, &number2);
    if (!errorWriteData)
    {
        return 0;
    }
	return errorWriteData;
}