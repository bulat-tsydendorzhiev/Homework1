#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "HashTable.h"
#include "console.h"

static void correctWord(char* word, const int wordLength)
{
    if (wordLength > 0 && !isalpha(word[wordLength - 1]))
    {
        word[wordLength - 1] = '\0';
    }
}

static ConsoleError loadData(HashTable* const table, const char* const filename)
{
    FILE* file = NULL;
    fopen_s(&file, filename, "r");
    if (file == NULL)
    {
        return openFileError;
    }

    while (!feof(file))
    {
        char word[50] = "";
        fscanf_s(file, "%s", word, 50);
        const int wordLength = strlen(word);
        correctWord(word, wordLength);
        if (wordLength > 0)
        {
            const bool successfulAdding = addValue(table, word);
            if (!successfulAdding)
            {
                fclose(file);
                return hashTableError;
            }
        }
    }

    fclose(file);
    return success;
}

ConsoleError runProgram(void)
{
    HashTable* table = createHashTable();
    if (table == NULL)
    {
        deleteHashTable(&table);
        return hashTableError;
    }

    const ConsoleError errorLoad = loadData(table, "mainFile.txt");
    if (errorLoad)
    {
        deleteHashTable(&table);
        return errorLoad;
    }


    printf("Words and their count\n");
    printf("---------------------\n");
    printHashTable(table);
    printf("---------------------\n");

    printf("Load factor = %f\n", getLoadFactor(table));
    printf("Average length of buckets = %f\n", getAverageBucketLength(table));
    printf("Max length of bucket = %Iu\n", getMaxBucketLength(table));

    deleteHashTable(&table);
    return success;
}