#pragma once

#include <stdbool.h>

typedef enum
{
    okAVL,
    outOfMemoryAVL,
    keyNotFound
} AVLTreeError;

// AVL-tree
typedef struct AVLTree AVLTree;

// The function create a tree;
// returns a pointer to the tree.
AVLTree* createAVLTree(void);

// The function adds (copies) a value to the tree;
// get a pointer to a tree, key, value.
AVLTreeError addValue(AVLTree* tree, const char* const key, const char* const value);

// The function returns a copy of the value by key;
// get a pointer to a tree, key.
char* getValueByKey(const AVLTree* const tree, const char* const key);

// Check for key existence;
// get a pointer to a tree, a key.
bool contains(const AVLTree* const tree, const char* const key);

// Delete the value by key;
// get a pointer to a tree, a key.
AVLTreeError deleteValue(AVLTree* tree, const char* const key);

// Delete tree;
// get a pointer to pointer to a tree.
void deleteTree(AVLTree** tree);