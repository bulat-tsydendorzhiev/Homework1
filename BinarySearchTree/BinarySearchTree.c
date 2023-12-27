#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "BinarySearchTree.h"

typedef struct Node
{
    int key;
    char* value;
    struct Node* leftSon;
    struct Node* rightSon;
} Node;

struct BinarySearchTree
{
    Node* root;
};

BinarySearchTree* createTree(void)
{
    return (BinarySearchTree*)calloc(1, sizeof(BinarySearchTree));
}

static Node* findNodeByKey(const Node* const node, const int key, Node** const parent)
{
    Node* currentNode = node;
    while (currentNode != NULL && currentNode->key != key)
    {
        if (parent != NULL)
        {
            *parent = currentNode;
        }

        if (key < currentNode->key)
        {
            currentNode = currentNode->leftSon;
        }
        else
        {
            currentNode = currentNode->rightSon;
        }
    }
    return currentNode;
}

BinarySearchTreeErrorCode insert(BinarySearchTree* tree, const int key, const char* const value)
{
    const char* newValue = _strdup(value);
    if (newValue == NULL)
    {
        return outOfMemoryBST;
    }

    Node* parent = NULL;
    Node* node = findNodeByKey(tree->root, key, &parent);
    if (node == NULL)
    {
        node = (Node*)calloc(1, sizeof(Node));
        if (node == NULL)
        {
            free(newValue);
            return outOfMemoryBST;
        }
        node->key = key;

        if (parent == NULL)
        {
            tree->root = node;
        }
        else
        {
            if (node->key < parent->key)
            {
                parent->leftSon = node;
            }
            else
            {
                parent->rightSon = node;
            }
        }
    }

    node->value = newValue;
    return okBST;
}

char* getValueByKey(const BinarySearchTree* const tree, const int key)
{
    Node* node = findNodeByKey(tree->root, key, NULL);
    return node == NULL ? NULL : node->value;
}

bool findKey(const BinarySearchTree* const tree, const int key)
{
    Node* node = findNodeByKey(tree->root, key, NULL);
    return node != NULL;
}

static Node* findMinValueSuccessor(const Node* const node, Node** const parent)
{
    Node* currentNode = node;
    while (currentNode->leftSon != NULL)
    {
        *parent = currentNode;
        currentNode = currentNode->leftSon;
    }
    return currentNode;
}

static Node* findMaxValueSuccessor(const Node* const node, Node** const parent)
{
    Node* currentNode = node;
    while (currentNode->rightSon != NULL)
    {
        *parent = currentNode;
        currentNode = currentNode->rightSon;
    }
    return currentNode;
}

static Node* findClosestSuccessor(const Node* const node, Node** const parent)
{
    Node* leftSuccessorParent = node;
    Node* leftSuccessor = findMaxValueSuccessor(node->leftSon, &leftSuccessorParent);
    Node* rightSuccessorParent = node;
    Node* rightSuccessor = findMinValueSuccessor(node->rightSon, &rightSuccessorParent);

    if (leftSuccessor == NULL && rightSuccessor == NULL)
    {
        return NULL;
    }

    if (leftSuccessor == NULL || rightSuccessor == NULL)
    {
        *parent = leftSuccessor == NULL ? rightSuccessorParent : leftSuccessorParent;
        return leftSuccessor == NULL ? rightSuccessor : leftSuccessor;
    }

    const int leftSuccessorDifference = abs(node->key - leftSuccessor->key);
    const int rightSuccessorDifference = abs(node->key - rightSuccessor->key);

    if (leftSuccessorDifference < rightSuccessorDifference)
    {
        *parent = leftSuccessorParent;
        return leftSuccessor;
    }
    else
    {
        *parent = rightSuccessorParent;
        return rightSuccessor;
    }
}

static void clearNode(Node** const node)
{
    if (*node == NULL)
    {
        return;
    }
    free((*node)->value);
    free(*node);
    *node = NULL;
}

BinarySearchTreeErrorCode deleteNode(BinarySearchTree* tree, const int key)
{
    Node* nodeParent = NULL;
    Node* node = findNodeByKey(tree->root, key, &nodeParent);
    if (node == NULL)
    {
        return keyNotFoundBST;
    }

    if (node->leftSon == NULL && node->rightSon == NULL)
    {
        if (node != tree->root)
        {
            if (nodeParent->leftSon == node)
            {
                nodeParent->leftSon = NULL;
            }
            else
            {
                nodeParent->rightSon = NULL;
            }
            clearNode(&node);
        }
        else
        {
            clearNode(&tree->root);
            tree->root = NULL;
        }
    }
    else if (node->leftSon == NULL || node->rightSon == NULL)
    {
        Node* temp = node->leftSon != NULL ? node->leftSon : node->rightSon;

        if (node != tree->root)
        {
            if (nodeParent->leftSon == node)
            {
                nodeParent->leftSon = temp;
            }
            else
            {
                nodeParent->rightSon = temp;
            }
            clearNode(&node);
        }
        else
        {
            clearNode(&tree->root);
            tree->root = temp;
        }
    }
    else
    {
        Node* successorParent = node;
        Node* successor = findClosestSuccessor(node, &successorParent);

        if (successorParent != node)
        {
            successorParent->leftSon = successor->rightSon;
            successor->rightSon = node->rightSon;
        }
        successor->leftSon = node->leftSon;
        if (node != tree->root)
        {
            if (nodeParent->leftSon == node)
            {
                nodeParent->leftSon = successor;
            }
            else
            {
                nodeParent->rightSon = successor;
            }
            clearNode(&node);
        }
        else
        {
            clearNode(&tree->root);
            tree->root = successor;
        }
    }
    return okBST;
}

static void clearTreeRecursion(Node* node)
{
    if (node == NULL)
    {
        return;
    }

    clearTreeRecursion(node->rightSon);
    clearTreeRecursion(node->leftSon);

    clearNode(&node);
}

void clearTree(BinarySearchTree** tree)
{
    clearTreeRecursion((*tree)->root);
    free(*tree);
    *tree = NULL;
}

void printCommands(void)
{
    printf("Выберите одну из следующих команд:\n");
    printf("0 - Выйти\n");
    printf("1 - Добавить значение по заданному ключу в словарь.\n");
    printf("2 - Получить значение по заданному ключу из словаря.\n");
    printf("3 - Проверить наличие заданного ключа в словаре.\n");
    printf("4 - Удалить заданный ключ и связанное с ним значение из словаря.\n");
    printf("Ваш выбор: ");
}