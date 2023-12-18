#include <stdio.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 100

bool isBalanced(const char* const string)
{
	size_t numberOfOpenBrackets = 0;
	for (size_t i = 0; string[i] != '\0'; ++i)
	{
		if (string[i] == '(')
		{
			++numberOfOpenBrackets;
		}
		else if (string[i] == ')')
		{
			if (numberOfOpenBrackets == 0)
			{
				return false;
			}
			--numberOfOpenBrackets;
		}
	}
	return numberOfOpenBrackets == 0;
}

int main()
{
	char string[MAX_STRING_LENGTH] = "";
	printf("Enter string with parentheses (length of string less than %d characters): ", MAX_STRING_LENGTH);
	scanf_s("%s", string, MAX_STRING_LENGTH);

	printf(isBalanced(string) ? "string is balanced\n": "string is not balanced\n");

	return 0;
}