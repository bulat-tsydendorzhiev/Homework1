#include <stdio.h>

#include "initData.h"

ErrorCode readArrayFromFile(const char* const fileName, int** const array, size_t* const arrayLength)
{
    if (fileName == NULL)
    {
        return nullFileName;
    }

    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        return openningFileError;
    }

    if (fscanf_s(file, "%Iu", arrayLength) != 1)
    {
        fclose(file);
        return scanError;
    }

    *array = (int*)calloc(*arrayLength, sizeof(int));
    if (*array == NULL)
    {
        fclose(file);
        return outOfMemory;
    }

    for (size_t i = 0; i < *arrayLength; ++i)
    {
        if (fscanf_s(file, "%d", &(*array)[i]) != 1)
        {
            free(*array);
            *array = NULL;
            fclose(file);
            return scanError;
        }
    }

    fclose(file);
    return success;
}