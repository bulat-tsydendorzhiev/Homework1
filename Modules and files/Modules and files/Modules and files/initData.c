#include <stdio.h>

#include "initData.h"

int readArrayFromFile(const char* const fileName, int** const array, size_t* const arrayLength)
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        return NULL;
    }

    if (fscanf_s(file, "%Iu", arrayLength) != 1)
    {
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