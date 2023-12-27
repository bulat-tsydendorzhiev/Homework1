#include <stdio.h>

#include "console.h"
#include "dataInit.h"
#include "realNumberLexer.h"

ErrorCode runProgram(void)
{
    printf("Enter string: ");
    char* string = getString();
    if (string == NULL)
    {
        printf("Lack of memry error\n");
        return outOfMemory;
    }

    printf(isRealNumber(string) ? "%s is a real number\n" : "%s is not a real number\n", string);
    free(string);
    return success;
}