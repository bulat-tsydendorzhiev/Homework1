#pragma once

#include <stdbool.h>

typedef struct Code
{
    size_t size;
    bool code[256];
} Code;

typedef struct HuffmanTree HuffmanTree;

HuffmanTree* makeLeaf(const char value, const size_t count);

size_t getCount(HuffmanTree* const treeArray);

HuffmanTree* makeTree(HuffmanTree** const tree1, HuffmanTree** const tree2);

Code* createCodeTable(const HuffmanTree* const tree);