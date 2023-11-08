#include <stdlib.h>

#include "HuffmanTree.h"

typedef struct Node
{
	char value;
	size_t count;
	struct Node* leftSon;
	struct Node* rightSon;
} Node;

struct HuffmanTree
{
	Node* root;
} ;

HuffmanTree* makeLeaf(const char value, const size_t count)
{
	Node* leaf = (Node*)calloc(count, sizeof(Node));
	if (leaf == NULL)
	{
		return NULL;
	}
	leaf->count = count;
	leaf->value = value;
	HuffmanTree* tree = (HuffmanTree*)calloc(count, sizeof(HuffmanTree));
	tree->root = leaf;
	return tree;
}

size_t getCount(HuffmanTree* const* const treeArray)
{
	return (*treeArray)->root->count;
}