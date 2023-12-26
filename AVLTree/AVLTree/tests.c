#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "AVLTree.h"
#include "tests.h"

#define NUMBER_OF_INSERTING_KEYS 8
#define NUMBER_OF_DELETING_KEYS 4
#define KEY_LENGTH 4
#define VALUE_LENGTH 25

static bool addKeys(AVLTree* tree, const char insertingKeys[NUMBER_OF_INSERTING_KEYS][KEY_LENGTH], const char insertingValues[NUMBER_OF_INSERTING_KEYS][VALUE_LENGTH])
{
    for (size_t i = 0; i < NUMBER_OF_INSERTING_KEYS; ++i)
    {
        const AVLTreeError errorInsert = addValue(tree, insertingKeys[i], insertingValues[i]);
        if (errorInsert)
        {
            return false;
        }
    }
    return true;
}

static bool runAddTest(const char insertingKeys[NUMBER_OF_INSERTING_KEYS][KEY_LENGTH], const char insertingValues[NUMBER_OF_INSERTING_KEYS][VALUE_LENGTH])
{
    AVLTree* tree = createAVLTree();
    if (tree == NULL)
    {
        return false;
    }

    for (size_t i = 0; i < NUMBER_OF_INSERTING_KEYS; ++i)
    {
        const AVLTreeError addingError = addValue(tree, insertingKeys[i], insertingValues[i]);
        if (addingError)
        {
            deleteTree(&tree);
            return false;
        }
    }

    deleteTree(&tree);
    return true;
}

static bool runContainsTest(const char insertingKeys[NUMBER_OF_INSERTING_KEYS][KEY_LENGTH], const char insertingValues[NUMBER_OF_INSERTING_KEYS][VALUE_LENGTH])
{
    AVLTree* tree = createAVLTree();
    if (tree == NULL)
    {
        return false;
    }

    const bool successfulAdding = addKeys(tree, insertingKeys, insertingValues);
    if (!successfulAdding)
    {
        deleteTree(&tree);
        return false;
    }

    for (size_t i = 0; i < NUMBER_OF_INSERTING_KEYS; ++i)
    {
        if (!contains(tree, insertingKeys[i]))
        {
            deleteTree(&tree);
            return false;
        }
    }

    deleteTree(&tree);
    return true;
}

static bool runGetValueTest(const char insertingKeys[NUMBER_OF_INSERTING_KEYS][KEY_LENGTH], const char insertingValues[NUMBER_OF_INSERTING_KEYS][VALUE_LENGTH])
{
    AVLTree* tree = createAVLTree();
    if (tree == NULL)
    {
        return false;
    }

    const bool successfulAdding = addKeys(tree, insertingKeys, insertingValues);
    if (!successfulAdding)
    {
        deleteTree(&tree);
        return false;
    }

    for (size_t i = 0; i < NUMBER_OF_INSERTING_KEYS; ++i)
    {
        const char* value = getValueByKey(tree, insertingKeys[i]);
        if (value == NULL || strcmp(value, insertingValues[i]) != 0)
        {
            deleteTree(&tree);
            return false;
        }
    }

    deleteTree(&tree);
    return true;
}

static bool runDeleteTest(const char insertingKeys[NUMBER_OF_INSERTING_KEYS][KEY_LENGTH], const char insertingValues[NUMBER_OF_INSERTING_KEYS][VALUE_LENGTH],
    const char deletingKeys[NUMBER_OF_DELETING_KEYS][KEY_LENGTH])
{
    AVLTree* tree = createAVLTree();
    if (tree == NULL)
    {
        return false;
    }

    const bool successfulAdding = addKeys(tree, insertingKeys, insertingValues);
    if (!successfulAdding)
    {
        deleteTree(&tree);
        return false;
    }

    for (size_t i = 0; i < NUMBER_OF_DELETING_KEYS; ++i)
    {
        const AVLTreeError errorDelete = deleteValue(tree, deletingKeys[i]);
        if (contains(tree, deletingKeys[i]) || errorDelete != okAVL)
        {
            deleteTree(&tree);
            return false;
        }
    }

    deleteTree(&tree);
    return true;
}

bool runTests(void)
{
    const char insertingKeys[NUMBER_OF_INSERTING_KEYS][KEY_LENGTH] = { "123", "56", "20", "70", "69", "200", "210", "124" };
    const char insertingValues[NUMBER_OF_INSERTING_KEYS][VALUE_LENGTH] = { "one hundred twenty three", "fifty six", "twenty", "seventy",
                                                                            "sixty nine", "two hundred", "two hundred ten", "one hundred twenty four" };
    const char deletingKeys[NUMBER_OF_DELETING_KEYS][KEY_LENGTH] = { "20", "70", "200", "123" };

    if (!runAddTest(insertingKeys, insertingValues))
    {
        return false;
    }
    if (!runContainsTest(insertingKeys, insertingValues))
    {
        return false;
    }
    if (!runGetValueTest(insertingKeys, insertingValues))
    {
        return false;
    }
    if (!runDeleteTest(insertingKeys, insertingValues, deletingKeys))
    {
        return false;
    }

    return true;
}