#include <stdio.h>
#include <locale.h>
#include <time.h>

int writeData(double* number, int* power);
double pow(double number, int power);
double fastPow(double number, int power);
int testPower(void);
int testFastPower(void);
int tests(void);

int main(void)
{
	setlocale(0, "Rus");
	double number; // число, возводимое в степень
	int power; // степень числа
	const int errorCode = writeData(&number, &power); // проверка на корректный ввод данных

	// проверка на ошибку
	if (!errorCode)
	{
		const int errorTest = tests();
		if (errorTest)
		{
			return errorTest;
		}
		const double result = pow(number, power);
		printf("%lf\n", result);
		return 0;
	}
	return errorCode;
}

int writeData(double* number, int* power)
{
	char check; // переменная для проверки на правильный тип данных 
	printf("Введите через пробел число и целую степень, в которую нужно возвести число: ");
	const int amountOfElements = scanf_s("%lf %d%c", number, power, &check);

	if (amountOfElements != 3 || (*number == 0 && *power < 0) || check != '\n') // защита от дурака
	{
		if (amountOfElements != 3 || check != '\n')
		{
			printf("Ошибка: некорректный ввод данных\n");
			return 1;
		}
		else if (*number == 0 && *power < 0)
		{
			printf("Ошибка: деление числа на 0\n");
			return 2;
		}
	}
	return 0;
}

double pow(double number, int power)
{
	// возведение в степень за O(n)
	double result = 1;
	if (power == 0 || number == 1)
	{
		return result;
	}
	else if (number == 0)
	{
		return 0;
	}
	else if (power > 0)
	{
		while (power > 0)
		{
			result *= number;
			power--;
		}
	}
	else
	{
		while (power < 0)
		{
			result /= number;
			power++;
		}
	}
	return result;
}

double fastPow(double number, int power)
{
	// возведение в степень за O(logn)
	double result = 1;
	if (power == 0 || number == 1)
	{
		return result;
	}
	else if (number == 0)
	{
		return 0;
	}
	else if (power > 0)
	{
		while (power > 0)
		{
			if (power % 2 == 0)
			{
				number *= number;
				power /= 2;
			}
			else
			{
				result *= number;
				power--;
			}
		}
		number = result;
	}
	else
	{
		while (power < 0)
		{
			if (power % 2 == 0)
			{
				number *= number;
				power /= 2;
			}
			else
			{
				result /= number;
				power++;
			}
		}
	}
	return result;
}

int testPower(void)
{
	// Тест 1: Возведение в степень 0
	if ((int)pow(5, 0) != 1)
	{
		return 1;
	}

	// Тест 2: Возведение в положительную степень
	if ((int)pow(2, 4) != 16)
	{
		return 2;
	}

	// Тест 3: Возведение в отрицательную степень
	if (pow(2, -2) != 0.250000)
	{
		return 3;
	}

	// Тест 4: Возведение в степень 1
	if ((int)pow(7, 1) != 7)
	{
		return 4;
	}

	// Тест 5: Возведение в степень больше 1
	if ((int)pow(4, 3) != 64)
	{
		return 5;
	}

	return 0;
}

int testFastPower(void)
{
	// Тест 1: Возведение в степень 0
	if ((int)fastPow(5, 0) != 1)
	{
		return 1;
	}

	// Тест 2: Возведение в положительную степень
	if ((int)fastPow(2, 4) != 16)
	{
		return 2;
	}

	// Тест 3: Возведение в отрицательную степень
	if (fastPow(2, -2) != 0.250000)
	{
		return 3;
	}

	// Тест 4: Возведение в степень 1
	if ((int)fastPow(7, 1) != 7)
	{
		return 4;
	}

	// Тест 5: Возведение в степень больше 1
	if ((int)fastPow(4, 3) != 64)
	{
		return 5;
	}

	return 0;
}

int tests(void)
{
	const int errorPowTest = testPower();
	if (errorPowTest)
	{
		printf("Тест для возведения в степень за O(n) не пройден\n");
		return errorPowTest;
	}

	int errorFastPowTest = testFastPower();
	if (errorFastPowTest)
	{
		printf("Тест для возведения в степень за O(logn) не пройден\n");
		return errorFastPowTest;
	}
}