#pragma once

#include <stdbool.h>

typedef enum
{
    okBST,
    keyNotFoundBST,
    outOfMemoryBST
} BinarySearchTreeErrorCode;

typedef enum
{
    quit,
    add,
    get,
    find,
    delete,
} Command;

typedef struct BinarySearchTree BinarySearchTree;

// Create binary search tree
BinarySearchTree* createTree(void);

// Add key and value to binary search tree
BinarySearchTreeErrorCode insert(BinarySearchTree* tree, const int key, const char* const value);

// Get value by key from binary search tree
char* getValueByKey(const BinarySearchTree* const tree, const int key);

// Check existence of key
// return true if key exists
bool findKey(const BinarySearchTree* const tree, const int key);

// Delete node with given key
// if key doesn't exist, function does nothing
BinarySearchTreeErrorCode deleteNode(BinarySearchTree* tree, const int key);

// Clear binary search tree
void clearTree(BinarySearchTree** tree);

// Print commands user can call
void printCommands(void);
