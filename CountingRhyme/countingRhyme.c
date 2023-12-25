#include <stdio.h>

#include "circularList.h"

int countPositionOfLastWarrior(const int numberOfWarriors, const int needTokillEvery)
{
    CircularList* warriors = createCircularList();
    if (warriors == NULL)
    {
        return -1;
    }
    for (size_t i = 1; i <= numberOfWarriors; ++i)
    {
        const bool successfullAppend = append(warriors, i);
        if (!successfullAppend)
        {
            clearCircularList(&warriors);
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