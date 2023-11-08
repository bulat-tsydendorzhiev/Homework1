#include <stdlib.h>
#include <string.h>

#include "Huffman.h"
#include "HuffmanTree.h"

#define ALPHABET_SIZE 256

void insertionSortStep(const HuffmanTree**const treeArray, const size_t index)
{
	for (size_t i = index; i >= 1 && getCount(treeArray[i - 1]) < getCount(treeArray[i]); --i)
	{
		HuffmanTree* temp = treeArray[i];
		treeArray[i] = treeArray[i - 1];
		treeArray[i - 1] = temp;
	}
}

size_t insertionSort(HuffmanTree** const treeArray, const size_t size)
{
	for (size_t i = 1; i < size; ++i)
	{
		insertionSortStep(treeArray, i);
	}
}

char* const compressString(const char* const string, size_t* const resultSize)
{
	size_t* const charCount = (size_t*)calloc(256, sizeof(size_t));
	const size_t stringLength = strlen(string);
	for (size_t i = 0; i < stringLength; ++i)
	{
		++charCount[string[i]];
	}

	HuffmanTree** treeArray = (HuffmanTree**)calloc(ALPHABET_SIZE, sizeof(HuffmanTree*));
	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
	{
		treeArray[i] = makeLeaf((char)i, charCount[i]);
	}
	insertionSort(treeArray, ALPHABET_SIZE);
    
}
