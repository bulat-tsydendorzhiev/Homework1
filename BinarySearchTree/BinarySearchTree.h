#pragma once

#include <stdbool.h>

typedef enum
{
	okBST,
	keyNotFoundBST,
	outOfMemoryBST
} BinarySearchTreeErrorCode;

typedef struct BinarySearchTree BinarySearchTree;

// Create binary search tree
BinarySearchTree* createTree(void);

// add key and value to binary search tree
BinarySearchTreeErrorCode insert(BinarySearchTree* tree, const int key, const char* const value);

// Get value by key from binary search tree
char* getValueByKey(const BinarySearchTree* const tree, const int key);

// Check existence of key
bool findKey(const BinarySearchTree* const tree, const int key);

// Delete node with given key
// If key doesn't exist, function does nothing
BinarySearchTreeErrorCode deleteNode(BinarySearchTree* tree, const int key);

// Clear binary search tree
void clearTree(BinarySearchTree** tree);
