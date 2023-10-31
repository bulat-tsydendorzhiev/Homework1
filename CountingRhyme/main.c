#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "countingRhyme.h"

bool* tests(bool* testsResults)
{
	const bool tests[][3] = { {5, 2, 3},
							 {10, 3, 4},
							 {15, 1, 15},
							 {1, 6, 1},
							 {25, 4, 15} };
	const int numberOfTests = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < numberOfTests; ++i)
	{
		const int numberOfWarriors = tests[i][0];
		const int needTokillEvery = tests[i][1];
		const int expectedResult = tests[i][2];

		const int result = getPositionOfLastWarrior(numberOfWarriors, needTokillEvery);
		testsResults[i] = (result == expectedResult);
	}
}

int main(void)
{
	bool* testsResults = malloc(sizeof(bool) * 5);
	if (testsResults == NULL)
	{
		printf("Out of memory error\n");
		return -1;
	}

	for (int i = 0; i < 5; ++i)
	{
		printf(testsResults[i] ? "Test %d passed\n": "Test %d failed", i + 1);
	}

	int numberOfWarriors = 0;
	int needTokillEvery = 0;
	const int errorInput = writeData(&numberOfWarriors, &needTokillEvery);
	if (errorInput)
	{
		printf("Error input\n");
		return errorInput;
	}

	const int positionOfLastWarrior = getPositionOfLastWarrior(numberOfWarriors, needTokillEvery);
	if (positionOfLastWarrior < 0)
	{
		printf("Circular list error\n");
		return positionOfLastWarrior;
	}
	printf("The last survived warrior with number %d\n", positionOfLastWarrior);

	free(testsResults);
	return 0;
}
