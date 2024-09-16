#include <stdlib.h>
#include <stdio.h>

#include "tests.h"
#include "BinarySearchTree.h"

#define NUMBER_OF_INSERTING_KEYS 8
#define NUMBER_OF_DELETING_KEYS 4
#define INSERTING_VALUE_LENGTH 25

static bool insertKeysAndValues(BinarySearchTree* tree, const int insertingKeys[NUMBER_OF_INSERTING_KEYS],
    const char insertingValues[NUMBER_OF_INSERTING_KEYS][INSERTING_VALUE_LENGTH])
{
    for (size_t i = 0; i < NUMBER_OF_INSERTING_KEYS; ++i)
    {
        BinarySearchTreeErrorCode errorInsert = insert(tree, insertingKeys[i], insertingValues[i]);
        if (errorInsert)
        {
            return false;
        }
    }
    return true;
}

static bool runInsertTest(const int insertingKeys[NUMBER_OF_INSERTING_KEYS], const char insertingValues[NUMBER_OF_INSERTING_KEYS][INSERTING_VALUE_LENGTH])
{
    BinarySearchTree* tree = createTree();
    if (tree == NULL)
    {
        return false;
    }

    for (size_t i = 0; i < NUMBER_OF_INSERTING_KEYS; ++i)
    {
        BinarySearchTreeErrorCode errorInsert = insert(tree, insertingKeys[i], insertingValues[i]);
        if (errorInsert)
        {
            clearTree(&tree);
            return false;
        }
    }

    clearTree(&tree);
    return true;
}

static bool runFindKeyTest(const int insertingKeys[NUMBER_OF_INSERTING_KEYS], const char insertingValues[NUMBER_OF_INSERTING_KEYS][INSERTING_VALUE_LENGTH])
{
    BinarySearchTree* tree = createTree();
    if (tree == NULL)
    {
        return false;
    }

    const bool successfulInsert = insertKeysAndValues(tree, insertingKeys, insertingValues);
    if (!successfulInsert)
    {
        clearTree(&tree);
        return false;
    }

    for (size_t i = 0; i < NUMBER_OF_INSERTING_KEYS; ++i)
    {
        if (!findKey(tree, insertingKeys[i]))
        {
            clearTree(&tree);
            return false;
        }
    }

    clearTree(&tree);
    return true;
}

static bool runGetValueTest(const int insertingKeys[NUMBER_OF_INSERTING_KEYS], const char insertingValues[NUMBER_OF_INSERTING_KEYS][INSERTING_VALUE_LENGTH])
{
    BinarySearchTree* tree = createTree();
    if (tree == NULL)
    {
        return false;
    }

    const bool successfulInsert = insertKeysAndValues(tree, insertingKeys, insertingValues);
    if (!successfulInsert)
    {
        clearTree(&tree);
        return false;
    }

    for (size_t i = 0; i < NUMBER_OF_INSERTING_KEYS; ++i)
    {
        const char* value = getValueByKey(tree, insertingKeys[i]);
        if (value == NULL)
        {
            clearTree(&tree);
            return false;
        }
    }

    clearTree(&tree);
    return true;
}

static bool runDeleteTest(const int insertingKeys[NUMBER_OF_INSERTING_KEYS], const char insertingValues[NUMBER_OF_INSERTING_KEYS][INSERTING_VALUE_LENGTH],
    const int deletingKeys[NUMBER_OF_DELETING_KEYS])
{
    BinarySearchTree* tree = createTree();
    if (tree == NULL)
    {
        return false;
    }

    const bool successfulInsert = insertKeysAndValues(tree, insertingKeys, insertingValues);
    if (!successfulInsert)
    {
        clearTree(&tree);
        return false;
    }

    for (size_t i = 0; i < NUMBER_OF_DELETING_KEYS; ++i)
    {
        const BinarySearchTreeErrorCode errorDelete = deleteNode(tree, deletingKeys[i]);
        if (errorDelete)
        {
            clearTree(&tree);
            return false;
        }
        if (findKey(tree, deletingKeys[i]))
        {
            clearTree(&tree);
            return false;
        }
    }

    clearTree(&tree);
    return true;
}

bool runTests(void)
{
    const int insertingKeys[NUMBER_OF_INSERTING_KEYS] = {123, 56, 20, 70, 69, 200, 210, 124};
    const char insertingValues[NUMBER_OF_INSERTING_KEYS][INSERTING_VALUE_LENGTH] = { "one hundred twenty three", "fifty six", "twenty", "seventy", "sixty nine", "two hundred",
                                        "two hundred ten", "one hundred twenty four" };
    const int deletingKeys[NUMBER_OF_DELETING_KEYS] = { 20, 70, 200, 123 };

    const bool insertTestPassed = runInsertTest(insertingKeys, insertingValues);
    if (!insertTestPassed)
    {
        printf("Тест вставки провалился\n");
        return false;
    }

    const bool findTestPassed = runFindKeyTest(insertingKeys, insertingValues);
    if (!findTestPassed)
    {
        printf("Тест поиска ключа провалился\n");
        return false;
    }

    const bool getValueTestPassed = runGetValueTest(insertingKeys, insertingValues);
    if (!getValueTestPassed)
    {
        printf("Тест получения значения по ключу провалился\n");
        return false;
    }

    const bool deletePassed = runDeleteTest(insertingKeys, insertingValues, deletingKeys);
    if (!deletePassed)
    {
        printf("Тест удаления провалился\n");
        return false;
    }

    return true;
}