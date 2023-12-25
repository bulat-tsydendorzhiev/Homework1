#include <stdio.h>

#include "dataInit.h"

#define MAX_STRING_LENGTH 100

DataInitErrorCode dataInit(FILE* stream, List* phoneBook)
{
    while (!feof(stream))
    {
        char name[MAX_STRING_LENGTH] = "";
        char phoneNumber[MAX_STRING_LENGTH] = "";
        if (fscanf_s(stream, "%s %s", name, MAX_STRING_LENGTH, phoneNumber, MAX_STRING_LENGTH) != 2)
        {
            printf("Incorrect format of data\n");
            return scanError;
        }
        const bool successfulAppend = append(phoneBook, name, phoneNumber);
        if (!successfulAppend)
        {
            return listOutOfMemory;
        }
    }
    return successInit;
}

DataInitErrorCode getKey(int* const key)
{
    printf("Sort(0 = by name, 1 = by phone number): ");
    return scanf_s("%d", key) != 1 || *key < 0 || *key > 1;
}