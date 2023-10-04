#include <stdio.h>
#include <string.h>

int isPalindrom(char* string, int stringLength)
{
	int st = 0;
	int end = stringLength - 1;
	while (st <= end)
	{
		if (string[st] == ' ')
		{
			st++;
			continue;
		}
		if (string[end] == ' ')
		{
			end--;
			continue;
		}

		if (string[st] != string[end])
		{
			return 0;
		}

		st++;
		end--;
	}
	return 1;
}

int tests(void)
{
	// тест 1: строка является палиндромом без пробелов
	char string1[] = "ololo";
	int length1 = strlen(string1);
	if (!isPalindrom(string1, length1))
	{
		return 1;
	}

	// тест 2: строка является палиндромом с пробелами
	char string2[] = "я иду с мечем судия";
	int length2 = strlen(string2);
	if (!isPalindrom(string2, length2))
	{
		return 2;
	}

	// тест 3: строка не является палиндромом
	char string3[] = "афыпфпыфп";
	int length3 = strlen(string3);
	if (isPalindrom(string3, length3))
	{
		return 3;
	}

	// тест 4: строка палиндром, но если учитывать, что заглавные буквы равны строчным
	char string4[] = "я Иду с мечем судия";
	int length4 = strlen(string4);
	if (isPalindrom(string4, length4))
	{
		return 4;
	}
	return 0;
}

int main(void)
{
	char* string;
	const int errorTest = tests();
	if (!errorTest)
	{
		printf("Tests passed succesfully!\n");
		return 0;
	}
	return errorTest;
}