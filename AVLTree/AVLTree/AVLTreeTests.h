#pragma once

typedef enum
{
    outOfMemory = -2,
    testFailed,
    testsPassed
} AVLTreeTestErrorCode;

// Tests to check the functionality of the AVL tree
AVLTreeTestErrorCode testsAVLTree(void);