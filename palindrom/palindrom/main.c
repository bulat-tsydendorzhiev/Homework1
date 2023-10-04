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
	// òåñò 1: ñòðîêà ÿâëÿåòñÿ ïàëèíäðîìîì áåç ïðîáåëîâ
	char string1[] = "ololo";
	int length1 = strlen(string1);
	if (!isPalindrom(string1, length1))
	{
		return 1;
	}

	// òåñò 2: ñòðîêà ÿâëÿåòñÿ ïàëèíäðîìîì ñ ïðîáåëàìè
	char string2[] = "ÿ èäó ñ ìå÷åì ñóäèÿ"; // пример из задания
	int length2 = strlen(string2);
	if (!isPalindrom(string2, length2))
	{
		return 2;
	}

	// òåñò 3: ñòðîêà íå ÿâëÿåòñÿ ïàëèíäðîìîì
	char string3[] = "àôûïôïûôï"; // рандомные буквы, не палиндром
	int length3 = strlen(string3);
	if (isPalindrom(string3, length3))
	{
		return 3;
	}

	// òåñò 4: ñòðîêà ïàëèíäðîì, íî åñëè ó÷èòûâàòü, ÷òî çàãëàâíûå áóêâû ðàâíû ñòðî÷íûì
	char string4[] = "ÿ Èäó ñ ìå÷åì ñóäèÿ"; // из примера только одна буква заглавная
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
