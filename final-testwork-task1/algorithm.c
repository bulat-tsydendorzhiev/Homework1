#include <string.h>

#include "algorithm.h"
#include "Qsort.h"

char* getMinNumber(const char* const number, const size_t length)
{
    qSort(number, 0, length - 1);
    char* minNumber = _strdup(number);
    return minNumber;
}