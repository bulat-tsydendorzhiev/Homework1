#include <stdlib.h>
#include <string.h>

#include "AVLTree.h"

typedef struct Node
{
    char* key;
    char* value;
    int height;
    struct Node* leftSon;
    struct Node* rightSon;
} Node;

struct AVLTree
{
    Node* root;
};

AVLTree* createAVLTree(void)
{
    return (AVLTree*)calloc(1, sizeof(AVLTree));
}

static int getHeight(Node* root)
{
    return (root == NULL) ? -1 : root->height;
}

static void updateHeight(Node* root)
{
    root->height = max(getHeight(root->leftSon), getHeight(root->rightSon)) + 1;
}

static int getBalance(Node* root)
{
    return (root == NULL) ? 0 : getHeight(root->rightSon) - getHeight(root->leftSon);
}

static Node* rotateLeft(Node* root)
{
    Node* pivot = root->rightSon;
    Node* c = pivot->leftSon;
    pivot->leftSon = root;
    root->rightSon = c;
    updateHeight(root);
    updateHeight(pivot);
    return pivot;
}

static Node* rotateRight(Node* root)
{
    Node* pivot = root->leftSon;
    Node* c = pivot->rightSon;
    pivot->rightSon = root;
    root->leftSon = c;
    updateHeight(root);
    updateHeight(pivot);
    return pivot;
}

static Node* bigRotateLeft(Node* root)
{
    root->rightSon = rotateRight(root->rightSon);
    return rotateLeft(root);
}

static Node* bigRotateRight(Node* root)
{
    root->leftSon = rotateLeft(root->leftSon);
    return rotateRight(root);
}

static Node* balance(Node* root)
{
    if (root == NULL)
    {
        return root;
    }

    updateHeight(root);
    if (getBalance(root) == 2)
    {
        if (getBalance(root->rightSon) >= 0)
        {
            return rotateLeft(root);
        }
        return bigRotateLeft(root);
    }
    else if (getBalance(root) == -2)
    {
        if (getBalance(root->leftSon) <= 0)
        {
            return rotateRight(root);
        }
        return bigRotateRight(root);
    }
    return root;
}

static Node* createNode(const char* const key, const char* const value)
{
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return NULL;
    }

    newNode->key = _strdup(key);
    newNode->value = _strdup(value);
    if (newNode->key == NULL || newNode->value == NULL)
    {
        return NULL;
    }
    newNode->height = 0;
    newNode->leftSon = NULL;
    newNode->rightSon = NULL;
    return newNode;
}

static Node* insertRecursive(Node* const root, const char* const key, char* value, AVLTreeError* error)
{
    if (root == NULL)
    {
        Node* newNode = createNode(key, value);
        *error = newNode == NULL;
        return newNode;
    }

    if (strcmp(key, root->key) == 0)
    {
        free(root->value);
        root->value = _strdup(value);
        *error = root->value == NULL;
    }
    else if (strcmp(key, root->key) < 0)
    {
        root->leftSon = insertRecursive(root->leftSon, key, value, error);
    }
    else
    {
        root->rightSon = insertRecursive(root->rightSon, key, value, error);
    }

    return balance(root);
}

AVLTreeError addValue(AVLTree* tree, const char* const key, const char* const value)
{
    AVLTreeError error = okAVL;
    tree->root = insertRecursive(tree->root, key, value, &error);
    return error;
}

static Node* findNodeByKey(Node* node, const char* const key)
{
    Node* currentNode = node;
    while (currentNode != NULL && strcmp(key, currentNode->key) != 0)
    {
        if (strcmp(key, currentNode->key) < 0)
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

char* getValueByKey(const AVLTree* const tree, const char* const key)
{
    Node* node = findNodeByKey(tree->root, key);
    return node == NULL ? NULL : node->value;
}

bool contains(const AVLTree* const tree, const char* const key)
{
    Node* node = findNodeByKey(tree->root, key);
    return node != NULL;
}

static Node* findSuccessor(const Node* const root)
{
    Node* currentNode = root;
    while (currentNode->rightSon != NULL)
    {
        currentNode = currentNode->rightSon;
    }
    return currentNode;
}

static void clearNode(Node** node)
{
    if (*node == NULL)
    {
        return;
    }
    free((*node)->key);
    free((*node)->value);
    free(*node);
    *node = NULL;
}

static Node* deleteNode(Node* root, const char* const key, AVLTreeError* error)
{
    if (root == NULL)
    {
        *error = keyNotFound;
        return root;
    }

    if (strcmp(key, root->key) < 0)
    {
        root->leftSon = deleteNode(root->leftSon, key, error);
    }
    else if (strcmp(key, root->key) > 0)
    {
        root->rightSon = deleteNode(root->rightSon, key, error);
    }
    else
    {
        if (root->leftSon == NULL || root->rightSon == NULL)
        {
            Node* temp = (root->rightSon == NULL) ? root->leftSon : root->rightSon;
            clearNode(&root);
            root = temp;
        }
        else
        {
            Node* successor = findSuccessor(root->leftSon);
            free(root->key);
            free(root->value);
            root->key = _strdup(successor->key);
            root->value = _strdup(successor->value);
            if (root->key == NULL || root->value == NULL)
            {
                *error = outOfMemoryAVL;
            }
            root->leftSon = deleteNode(root->leftSon, root->key, error);
        }
    }

    return balance(root);
}

AVLTreeError deleteValue(AVLTree* tree, const char* const key)
{
    AVLTreeError error = okAVL;
    tree->root = deleteNode(tree->root, key, &error);
    return error;
}

static void deleteTreeRecursive(Node* node)
{
    if (node == NULL)
    {
        return;
    }

    deleteTreeRecursive(node->rightSon);
    deleteTreeRecursive(node->leftSon);

    clearNode(&node);
}

void deleteTree(AVLTree** tree)
{
    deleteTreeRecursive((*tree)->root);
    free(*tree);
    *tree = NULL;
}
