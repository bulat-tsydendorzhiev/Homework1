#include <stdio.h>

#include "circularList.h"

int writeData(int* numberOfWarriors, int* needTokillEvery)
{
	char check = ' ';
	printf("Number of warriors: ");
	int numberOfValues = scanf_s("%d%c", numberOfWarriors, &check);
	if (numberOfValues != 2 || check != '\n' || * numberOfWarriors < 1)
	{
		return -1;
	}

	printf("Need to kill every: ");
	numberOfValues = scanf_s("%d%c", needTokillEvery, &check);

	if (numberOfValues != 2 || check != '\n' || *needTokillEvery < 1)
	{
		return -1;
	}

	return 0;
}

int getPositionOfLastWarrior(const int numberOfWarriors, const int needTokillEvery)
{
	CircularList* warriors = NULL;
	const CircularListError creationError =  createCircularList(&warriors);
	if (creationError)
	{
		return -1;
	}

	for (int i = 1; i <= numberOfWarriors; ++i)
	{
		append(&warriors, i);
	}

	while (!onlyOneLeft(warriors))
	{
		deletePosition(&warriors, needTokillEvery);
	}

	const int answer = getHeadValue(warriors);

	clearCircularList(&warriors);
	return answer;
}