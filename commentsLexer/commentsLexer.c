#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "commentsLexer.h"

#define NAME_OF_FILE_WITH_TABLE "table.txt"
#define NUMBER_OF_ROWS 6
#define NUMBER_OF_COLUMNS 3

typedef enum
{
    start,
    openingSlash,
    firstAsterisk,
    inComment,
    secondAsterisk,
    endOfComment
} State;

enum tableStates
{
    slash,
    asterisk,
    comment
};

static bool createTable(int table[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS])
{
    FILE* fileWithTable = NULL;
    fopen_s(&fileWithTable, NAME_OF_FILE_WITH_TABLE, "r");
    if (fileWithTable == NULL)
    {
        return false;
    }
    for (size_t i = 0; i < NUMBER_OF_ROWS; ++i)
    {
        for (size_t j = 0; j < NUMBER_OF_COLUMNS; ++j)
        {
            if (fscanf_s(fileWithTable, "%d", &table[i][j]) != 1)
            {
                fclose(fileWithTable);
                return false;
            }
        }
    }

    fclose(fileWithTable);
    return true;
}

static State getNextState(const State currentState, const char character, const int table[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS])
{
    switch (character)
    {
    case '/':
        return table[currentState][slash];
    case '*':
        return table[currentState][asterisk];
    default:
        return table[currentState][comment];
    }
}

static bool writeCharacterInComment(char** comments, const char character, size_t* const index, size_t* const capacity)
{
    (*comments)[*index] = character;
    ++(*index);
    if (*index >= *capacity)
    {
        char* temp = (char*)realloc((*comments), (*capacity) * 2 * sizeof(char));
        if (temp == NULL)
        {
            return false;
        }
        (*comments) = temp;
        (*capacity) *= 2;
    }
    return true;
}

char* getComments(FILE* const file)
{
    int table[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] = { 0 };
    const bool successfulCreate = createTable(table);
    if (!successfulCreate)
    {
        return NULL;
    }

    size_t index = 0;
    size_t capacity = 4;
    char* comments = (char*)calloc(capacity, sizeof(char));
    if (comments == NULL)
    {
        return NULL;
    }

    State state = start;
    while (!feof(file))
    {
        const char character = fgetc(file);
        state = getNextState(state, character, table);
        switch (state)
        {
        case firstAsterisk:
        {
            bool successfulAdding = writeCharacterInComment(&comments, '/', &index, &capacity);
            if (!successfulAdding)
            {
                return NULL;
            }
            successfulAdding = writeCharacterInComment(&comments, '*', &index, &capacity);
            if (!successfulAdding)
            {
                return NULL;
            }
            break;
        }
        case inComment:
        case secondAsterisk:
        {
            const bool successfulAdding = writeCharacterInComment(&comments, character, &index, &capacity);
            if (!successfulAdding)
            {
                return NULL;
            }
            break;
        }
        case endOfComment:
        {
            bool successfulAdding = writeCharacterInComment(&comments, character, &index, &capacity);
            if (!successfulAdding)
            {
                return NULL;
            }
            break;
        }
        }
    }

    for (size_t i = index; i < capacity; ++i)
    {
        comments[i] = '\0';
    }

    return comments;
}
