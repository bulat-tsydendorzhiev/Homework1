#pragma once

#include <stdbool.h>

typedef enum
{
    okAVL,
    outOfMemoryAVL = 2,
    keyNotFound
} AVLTreeError;

typedef enum 
{
    quit,
    add,
    get,
    find,
    delete,
} Command;

// AVL-tree
typedef struct AVLTree AVLTree;

// Create a tree
AVLTree* createAVLTree(void);

// Add a value by key to the tree / replace a value by key with new value
AVLTreeError addValue(AVLTree* tree, const char* const key, const char* const value);

// Return a pointer of the value by key
char* getValueByKey(const AVLTree* const tree, const char* const key);

// Check for key existence
bool contains(const AVLTree* const tree, const char* const key);

// Delete the value by key
AVLTreeError deleteValue(AVLTree* tree, const char* const key);

// Delete tree
void deleteTree(AVLTree** tree);

// Print commands for user
void printCommands(void);
