#include <stdio.h>

#include "circularList.h"

int countPositionOfLastWarrior(const int numberOfWarriors, const int needTokillEvery)
{
	CircularList* warriors = createCircularList();
	for (int i = 1; i <= numberOfWarriors; ++i)
	{
		bool successfullAppend = append(warriors, i);
		if (!successfullAppend)
		{
			return -1;
		}
	}

	while (!isOnlyOneLeft(warriors))
	{
		deletePosition(warriors, needTokillEvery);
	}

	const int answer = getHeadValue(warriors);
	clearCircularList(&warriors);
	return answer;
}