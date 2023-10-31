#include <stdio.h>

#include "IntStack.h"
#include "CharStack.h"
#include "StackTests.h"

int main(void)
{
	const TestErrorCode testIntErrorCode = intStackTests();
	if (testIntErrorCode)
	{
		printf("int stack test failed\n");
		return testIntErrorCode;
	}

	const TestErrorCode testCharErrorCode = charStackTests();
	if (testCharErrorCode)
	{
		printf("char stack test failed\n");
		return testCharErrorCode;
	}

	printf("Tests passed succesfully!\n");

	return 0;
}