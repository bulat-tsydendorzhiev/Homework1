#include <stdio.h>

#include "console.h"
#include "countingRhyme.h"

static int readData(int* const numberOfWarriors, int* const needTokillEvery)
{
    printf("Number of warriors: ");
    scanf_s("%d", numberOfWarriors);
    printf("Need to kill every: ");
    scanf_s("%d", needTokillEvery);
    if (*numberOfWarriors < 1 || *needTokillEvery < 1)
    {
        return wrongInput;
    }
    return success;
}

ConsoleErrorCode runProgram(void)
{
    int numberOfWarriors = 0;
    int needTokillEvery = 0;
    const ConsoleErrorCode errorInput = readData(&numberOfWarriors, &needTokillEvery);
    if (errorInput)
    {
        printf("Error input\n");
        return wrongInput;
    }

    const int positionOfLastWarrior = countPositionOfLastWarrior(numberOfWarriors, needTokillEvery);
    if (positionOfLastWarrior < 0)
    {
        printf("Circular list error\n");
        return circularListError;
    }
    printf("The last survived warrior with number %d\n", positionOfLastWarrior);

    return success;
}