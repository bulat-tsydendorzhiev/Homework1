#include "searchMostFrequent.h"

int searchMostFrequent(const int* const array, const size_t arrayLength)
{
    int answer = array[0];
    size_t count = 1, maxCount = 0;

    for (size_t i = 1; i < arrayLength; ++i)
    {
        if (array[i - 1] == array[i])
        {
            ++count;
            if (count > maxCount)
            {
                maxCount = count;
                answer = array[i - 1];
            }
        }
        else
        {
            count = 1;
        }
    }
    return answer;
}