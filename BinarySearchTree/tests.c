#include <stdlib.h>

#include "tests.h"
#include "BinarySearchTree.h"

TestErrorCode tests(void)
{
    BinarySearchTree* tree = createTree();
    if (tree == NULL)
    {
        return testFailed;
    }

    // Тест 1: проверка работы функции insert
    insert(tree, 123, "one hundred twenty three");
    if (!findKey(tree, 123) || getValueByKey(tree, 123) == NULL)
    {
        clearTree(&tree);
        return testFailed;
    }

    insert(tree, 56, "fifty six");
    insert(tree, 20, "twenty");
    insert(tree, 70, "seventy");
    insert(tree, 69, "sixty nine");
    insert(tree, 200, "two hundred");
    insert(tree, 210, "two hundred ten");
    insert(tree, 124, "one hundred twenty four");

    /*
    Для наглядности
              123
             _/ \_
           _/     \_
          /         \
        56          200
        /\         /   \
       /  \      124   210
      20  70
          /
         69
    */

    // Тест 2: удаление листа
    deleteNode(tree, 20);
    char* value = getValueByKey(tree, 20);
    if (findKey(tree, 20) || value != NULL)
    {
        return testFailed;
    }
    free(value);

    // Тест 3: удаление узлов, у которых есть хотя бы один потомок
    const int deletingKey[] = { 70, 200, 123 };

    for (int i = 0; i < 3; ++i)
    {
        deleteNode(tree, deletingKey[i]);
        if (findKey(tree, deletingKey[i]))
        {
            clearTree(&tree);
            return testFailed;
        }
    }

    clearTree(&tree);
    return testsPassed;
}