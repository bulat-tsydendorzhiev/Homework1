#include <stdlib.h>
#include <memory.h>

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

size_t getCount(HuffmanTree* const treeArray)
{
	return treeArray != NULL ? treeArray->root->count: 0;
}

HuffmanTree* makeTree(HuffmanTree** const tree1, HuffmanTree** const tree2)
{
	HuffmanTree* newTree = makeLeaf('\0', getCount(*tree1) + getCount(*tree2));
	newTree->root->leftSon = (*tree1)->root;
	newTree->root->rightSon = (*tree2)->root;

	free(*tree1);
	free(*tree2);
	*tree1 = NULL;
	*tree2 = NULL;

	return newTree;
}

void makeCode(size_t position, bool code[256], Node* current, Code* codeTable)
{
	if (current->leftSon == NULL)
	{
		codeTable[current->value].size = position;
		memcpy_s(codeTable[current->value].code, 256 * sizeof(bool), code, 256 * sizeof(bool));
		return;
	}
	code[position] = 0;
	makeCode(position + 1, code, current->leftSon, codeTable);
	code[position] = 1;
	makeCode(position + 1, code, current->rightSon, codeTable);
}

Code* createCodeTable(const HuffmanTree* const tree)
{
	Code* codeTable = (Code*)calloc(256, sizeof(Code));
	bool code[256] = { false };
	makeCode(0, code, tree->root, codeTable);
	return codeTable;
}
