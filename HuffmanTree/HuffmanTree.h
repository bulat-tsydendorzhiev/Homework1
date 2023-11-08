#pragma once

typedef struct HuffmanTree HuffmanTree;

HuffmanTree* makeLeaf(const char value, const size_t count);

size_t getCount(HuffmanTree* const* const treeArray);
