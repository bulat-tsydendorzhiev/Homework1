#include <stdlib.h>

#include "tests.h"
#include "BinarySearchTree.h"

static void insertKeys(BinarySearchTree* tree, const int insertingKeys[8], const char insertingValues[8][25])
{
    for (size_t i = 0; i < 8; ++i)
    {
        insert(tree, insertingKeys[i], insertingValues[i]);
    }
}

static TestErrorCode insertTest(const int insertingKeys[8], const char insertingValues[8][25])
{
    BinarySearchTree* tree = createTree();
    if (tree == NULL)
    {
        clearTree(&tree);
        return outOfMemory;
    }

    for (size_t i = 0; i < 8; i++)
    {
        BinarySearchTreeErrorCode errorInsert = insert(tree, insertingKeys[i], insertingValues[i]);
        if (errorInsert)
        {
            clearTree(&tree);
            return testFailed;
        }
    }

    clearTree(&tree);
    return testsPassed;
}

static TestErrorCode findKeyTest(const int insertingKeys[8], const char insertingValues[8][25])
{
    BinarySearchTree* tree = createTree();
    if (tree == NULL)
    {
        clearTree(&tree);
        return outOfMemory;
    }

    insertKeys(tree, insertingKeys, insertingValues);
    for (size_t i = 0; i < 8; i++)
    {
        if (!findKey(tree, insertingKeys[i]))
        {
            clearTree(&tree);
            return testFailed;
        }
    }

    clearTree(&tree);
    return testsPassed;
}

static TestErrorCode getValueTest(const int insertingKeys[8], const char insertingValues[8][25])
{
    BinarySearchTree* tree = createTree();
    if (tree == NULL)
    {
        clearTree(&tree);
        return outOfMemory;
    }

    insertKeys(tree, insertingKeys, insertingValues);

    for (size_t i = 0; i < 8; i++)
    {
        const char* value = getValueByKey(tree, insertingKeys[i]);
        if (value == NULL)
        {
            clearTree(&tree);
            return testFailed;
        }
    }

    clearTree(&tree);
    return testsPassed;
}

static TestErrorCode deleteTest(const int insertingKeys[8], const char insertingValues[8][25], const int deletingKeys[4])
{
    BinarySearchTree* tree = createTree();
    if (tree == NULL)
    {
        clearTree(&tree);
        return outOfMemory;
    }

    insertKeys(tree, insertingKeys, insertingValues);

    for (size_t i = 0; i < 4; ++i)
    {
        deleteNode(tree, deletingKeys[i]);
        if (findKey(tree, deletingKeys[i]))
        {
            clearTree(&tree);
            return testFailed;
        }
    }

    clearTree(&tree);
    return testsPassed;
}

TestErrorCode tests(void)
{
    BinarySearchTree* tree = createTree();
    if (tree == NULL)
    {
        return outOfMemory;
    }
    const int insertingKeys[8] = {123, 56, 20, 70, 69, 200, 210, 124};
    const char insertingValues[8][25] = { "one hundred twenty three", "fifty six", "twenty", "seventy", "sixty nine", "two hundred", "two hundred ten", "one hundred twenty four" };
    const int deletingKeys[4] = { 20, 70, 200, 123 };

    const TestErrorCode errorAdd = insertTest(insertingKeys, insertingValues);
    if (errorAdd)
    {
        return addTestFailed;
    }

    const TestErrorCode errorFind = findKeyTest(insertingKeys, insertingValues);
    if (errorFind)
    {
        return findKeyTestFailed;
    }
    const TestErrorCode errorGetValue = getValueTest(insertingKeys, insertingValues);
    if (errorGetValue)
    {
        return getValueTestFailed;
    }
    const TestErrorCode errorDelete = deleteTest(insertingKeys, insertingValues, deletingKeys);
    if (errorDelete)
    {
        return deleteTestFailed;
    }

    return testsPassed;
}