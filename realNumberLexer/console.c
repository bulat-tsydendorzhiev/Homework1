#include <stdio.h>

#include "console.h"
#include "dataInit.h"
#include "realNumberLexer.h"

ErrorCode runProgram(void)
{
    size_t length = 0;
    printf("Enter string: ");
    char* string = getString(&length);
    if (string == NULL)
    {
        return outOfMemory;
    }

    printf(isRealNumber(string, length) ? "%s is a real number\n" : "%s is not a real number\n", string);
    free(string);
    return success;
}