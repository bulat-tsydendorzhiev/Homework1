#include <stdlib.h>
#include <stdio.h>

#include "AVLTree.h"
#include "AVLTreeTests.h"

static void addKeys(AVLTree* tree, const char insertingKeys[8][4], const char insertingValues[8][25])
{
    for (size_t i = 0; i < 8; ++i)
    {
        addValue(tree, insertingKeys[i], insertingValues[i]);
    }
}

static AVLTreeTestErrorCode addTest(const char insertingKeys[8][4], const char insertingValues[8][25])
{
    AVLTree* tree = createAVLTree();
    if (tree == NULL)
    {
        deleteTree(&tree);
        return outOfMemory;
    }

    for (size_t i = 0; i < 8; i++)
    {
        AVLTreeTestErrorCode errorInsert = addValue(tree, insertingKeys[i], insertingValues[i]);
        if (errorInsert)
        {
            deleteTree(&tree);
            return testFailed;
        }
    }

    deleteTree(&tree);
    return testsPassed;
}

static AVLTreeTestErrorCode containsTest(const char insertingKeys[8][4], const char insertingValues[8][25])
{
    AVLTree* tree = createAVLTree();
    if (tree == NULL)
    {
        deleteTree(&tree);
        return outOfMemory;
    }

    addKeys(tree, insertingKeys, insertingValues);
    for (size_t i = 0; i < 8; i++)
    {
        if (!contains(tree, insertingKeys[i]))
        {
            deleteTree(&tree);
            return testFailed;
        }
    }

    deleteTree(&tree);
    return testsPassed;
}

static AVLTreeTestErrorCode getValueTest(const char insertingKeys[8][4], const char insertingValues[8][25])
{
    AVLTree* tree = createAVLTree();
    if (tree == NULL)
    {
        deleteTree(&tree);
        return outOfMemory;
    }

    addKeys(tree, insertingKeys, insertingValues);

    for (size_t i = 0; i < 8; i++)
    {
        const char* value = getValueByKey(tree, insertingKeys[i]);
        if (value == NULL)
        {
            deleteTree(&tree);
            return testFailed;
        }
    }

    deleteTree(&tree);
    return testsPassed;
}

static AVLTreeTestErrorCode deleteTest(const char insertingKeys[8][4], const char insertingValues[8][25], const char deletingKeys[4][4])
{
    AVLTree* tree = createAVLTree();
    if (tree == NULL)
    {
        deleteTree(&tree);
        return outOfMemory;
    }

    addKeys(tree, insertingKeys, insertingValues);

    for (size_t i = 0; i < 4; ++i)
    {
        AVLTreeError errorDelete = deleteValue(tree, deletingKeys[i]);
        if (contains(tree, deletingKeys[i]) || errorDelete != okAVL)
        {
            deleteTree(&tree);
            return testFailed;
        }
    }

    deleteTree(&tree);
    return testsPassed;
}

AVLTreeTestErrorCode testsAVLTree(void)
{
    AVLTree* tree = createAVLTree(); // Check for creating of AVL tree
    if (tree == NULL)
    {
        deleteTree(&tree);
        return outOfMemory;
    }
    deleteTree(&tree);

    const char insertingKeys[8][4] = { "123", "56", "20", "70", "69", "200", "210", "124" };
    const char insertingValues[8][25] = { "one hundred twenty three", "fifty six", "twenty", "seventy", "sixty nine", "two hundred", "two hundred ten", "one hundred twenty four" };
    const char deletingKeys[4][4] = { "20", "70", "200", "123" };

    AVLTreeTestErrorCode resultOfTests[] = { addTest(insertingKeys, insertingValues),
                                            containsTest(insertingKeys, insertingValues),
                                            getValueTest(insertingKeys, insertingValues),
                                            deleteTest(insertingKeys, insertingValues, deletingKeys) };

    const char nameOfTest[][60] = { "тест вставки элемента",
                                "тест проверки наличия ключа",
                                "тест получения значения",
                                "тест удаления значения по ключу" };

    const size_t numberOfTests = sizeof(resultOfTests) / sizeof(resultOfTests[0]);
    for (size_t i = 0; i < numberOfTests; i++)
    {
        AVLTreeTestErrorCode error = resultOfTests[i];
        if (error)
        {
            printf("%s провалился с кодом ошибки: %d\n", nameOfTest[i], error);
        }
    }

    return testsPassed;
}