#include <stdlib.h>
#include <string.h>

#include "BinarySearchTree.h"

typedef struct Node
{
	int key;
	char* value;
	struct Node* leftSon;
	struct Node* rightSon;
} Node;

struct BinarySearchTree
{
	Node* root;
};

BinarySearchTree* createTree(void)
{
	return (BinarySearchTree*)calloc(1, sizeof(BinarySearchTree));
}

static char* updateValue(const char* const newString)
{
	const size_t length = strlen(newString) + 1;
	char* updatedString = (char*)malloc(sizeof(char) * length);
	if (updatedString == NULL)
	{
		free(updatedString);
		return NULL;
	}
	strcpy_s(updatedString, length, newString);
	return updatedString;
}

static Node* createNode(const int key, const char* const value)
{
	Node* newNode = (Node*)calloc(1, sizeof(Node));
	if (newNode == NULL)
	{
		return NULL;
	}
	newNode->key = key;
	newNode->value = updateValue(value);
	if (newNode->value == NULL)
	{
		return NULL;
	}
	newNode->leftSon = NULL;
	newNode->rightSon = NULL;
	return newNode;
}

static Node* findNodeByKey(Node* node, const int key, Node** parent)
{
	Node* currentNode = node;
	while (currentNode != NULL && currentNode->key != key)
	{
		if (parent != NULL)
		{
			*parent = currentNode;
		}

		if (key < currentNode->key)
		{
			currentNode = currentNode->leftSon;
		}
		else
		{
			currentNode = currentNode->rightSon;
		}
	}
	return currentNode;
}

BinarySearchTreeErrorCode insert(BinarySearchTree* tree, const int key, const char* const value)
{
	Node* parent = NULL;
	Node* node = findNodeByKey(tree->root, key, &parent);
	if (node == NULL)
	{
		node = (Node*)malloc(sizeof(Node));
		if (node == NULL)
		{
			return outOfMemoryBST;
		}
		node->key = key;
		node->leftSon = NULL;
		node->rightSon = NULL;

		if (parent == NULL)
		{
			tree->root = node;
		}
		else
		{
			if (node->key < parent->key)
			{
				parent->leftSon = node;
			}
			else
			{
				parent->rightSon = node;
			}
		}
	}
	else
	{
		free(node->value);
		node->value = NULL;
	}
	node->value = updateValue(value);
	if (node->value == NULL)
	{
		return outOfMemoryBST;
	}
	return okBST;
}

char* getValueByKey(const BinarySearchTree* const tree, const int key)
{
	Node* node = findNodeByKey(tree->root, key, NULL);
	return node == NULL ? NULL : node->value;
}

bool findKey(const BinarySearchTree* const tree, const int key)
{
	Node* node = findNodeByKey(tree->root, key, NULL);
	return node != NULL;
}

static Node* findMinValueSuccessor(const Node* const node, Node** const parent)
{
	Node* currentNode = node;
	while (currentNode->leftSon != NULL)
	{
		*parent = currentNode;
		currentNode = currentNode->leftSon;
	}
	return currentNode;
}

static Node* findMaxValueSuccessor(const Node* const node, Node** const parent)
{
	Node* currentNode = node;
	while (currentNode->rightSon != NULL)
	{
		*parent = currentNode;
		currentNode = currentNode->rightSon;
	}
	return currentNode;
}

static Node* findClosestSuccessor(const Node* const node, Node** const parent)
{
	Node* leftSuccessorParent = node;
	Node* leftSuccessor = findMaxValueSuccessor(node->leftSon, &leftSuccessorParent);
	Node* rightSuccessorParent = node;
	Node* rightSuccessor = findMinValueSuccessor(node->rightSon, &rightSuccessorParent);

	if (leftSuccessor == NULL && rightSuccessor == NULL)
	{
		return NULL;
	}

	if (leftSuccessor == NULL || rightSuccessor == NULL)
	{
		*parent = leftSuccessor == NULL ? rightSuccessorParent : leftSuccessorParent;
		return leftSuccessor == NULL ? rightSuccessor : leftSuccessor;
	}

	const int leftSuccessorDifference = abs(node->key - leftSuccessor->key);
	const int rightSuccessorDifference = abs(node->key - rightSuccessor->key);

	if (leftSuccessorDifference < rightSuccessorDifference)
	{
		*parent = leftSuccessorParent;
		return leftSuccessor;
	}
	else
	{
		*parent = rightSuccessorParent;
		return rightSuccessor;
	}
}

static void clearNode(Node** const node)
{
	if (*node == NULL)
	{
		return;
	}
	free((*node)->value);
	free(*node);
	*node = NULL;
}

BinarySearchTreeErrorCode deleteNode(BinarySearchTree* tree, const int key)
{
	Node* nodeParent = NULL;
	Node* node = findNodeByKey(tree->root, key, &nodeParent);
	if (node == NULL)
	{
		return keyNotFoundBST;
	}

	if (node->leftSon == NULL && node->rightSon == NULL)
	{
		if (node != tree->root)
		{
			if (nodeParent->leftSon == node)
			{
				nodeParent->leftSon = NULL;
			}
			else
			{
				nodeParent->rightSon = NULL;
			}
			clearNode(&node);
		}
		else
		{
			clearNode(&tree->root);
			tree->root = NULL;
		}
	}
	else if (node->leftSon == NULL || node->rightSon == NULL)
	{
		Node* temp = node->leftSon != NULL ? node->leftSon : node->rightSon;

		if (node != tree->root)
		{
			if (nodeParent->leftSon == node)
			{
				nodeParent->leftSon = temp;
			}
			else
			{
				nodeParent->rightSon = temp;
			}
			clearNode(&node);
		}
		else
		{
			clearNode(&tree->root);
			tree->root = temp;
		}
	}
	else
	{
		Node* successorParent = node;
		Node* successor = findClosestSuccessor(node, &successorParent);

		if (successorParent != node)
		{
			successorParent->leftSon = successor->rightSon;
			successor->rightSon = node->rightSon;
		}
		successor->leftSon = node->leftSon;
		if (node != tree->root)
		{
			if (nodeParent->leftSon == node)
			{
				nodeParent->leftSon = successor;
			}
			else
			{
				nodeParent->rightSon = successor;
			}
			clearNode(&node);
		}
		else
		{
			clearNode(&tree->root);
			tree->root = successor;
		}
	}
	return okBST;
}

static void clearTreeRecursion(Node* node)
{
	if (node == NULL)
	{
		return;
	}

	clearTreeRecursion(node->rightSon);
	clearTreeRecursion(node->leftSon);

	clearNode(&node);
}

void clearTree(BinarySearchTree** tree)
{
	clearTreeRecursion((*tree)->root);
	free(*tree);
	*tree = NULL;
}
