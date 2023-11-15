#include <stdlib.h>
#include <stdio.h>

#include "parseTree.h"

typedef struct Node
{
	int value;
	struct Node* leftSon;
	struct Node* rightSon;
} Node;

struct ParseTree
{
	Node* root;
};

ParseTree* createParseTree(void)
{
	return (ParseTree*)calloc(1, sizeof(ParseTree));
}

static Node* createNode(const int value)
{
	Node* newNode = (Node*)calloc(1, sizeof(Node));
	if (newNode == NULL)
	{
		return NULL;
	}
	newNode->value = value;
	newNode->leftSon = NULL;
	newNode->rightSon = NULL;
	return newNode;
}

static bool isOperation(const char symbol)
{
	return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

static bool isDigit(const char symbol)
{
	return symbol >= '0' && symbol <= '9';
}

static int getNumber(FILE* file)
{
	int number = 0;
	int symbol = fgetc(file);
	while (isDigit(symbol))
	{
		number = number * 10 + symbol - '0';
		symbol = fgetc(file);
	}
	ungetc(symbol, file);
	return number;
}

static Node* buildParseTreeResursive(FILE* file)
{
	Node* node = NULL;
	char symbol = fgetc(file);
	while (symbol != ')' && !feof(file))
	{
		if (isDigit(symbol))
		{
			ungetc(symbol, file);
			node = createNode(getNumber(file));
			if (node == NULL)
			{
				return NULL;
			}
			return node;
		}
		else if (isOperation(symbol))
		{
			node = createNode((int)symbol);
			if (node == NULL)
			{
				return NULL;
			}
			node->leftSon = buildParseTreeResursive(file);
			node->rightSon = buildParseTreeResursive(file);
			if (node->leftSon == NULL || node->rightSon == NULL)
			{
				return NULL;
			}
		}
		symbol = fgetc(file);
	}
	return node;
}

static void clearNodes(Node* root)
{
	if (root == NULL)
	{
		return;
	}

	clearNodes(root->leftSon);
	clearNodes(root->rightSon);
	free(root);
}

void clearParseTree(ParseTree** tree)
{
	free((*tree)->root);
	free(*tree);
	*tree = NULL;
}

ParseTreeError buildParseTree(ParseTree** tree, const char* const filename)
{
	FILE* file = NULL;
	fopen_s(&file, filename, "r");
	if (file == NULL)
	{
		fclose(file);
		clearParseTree(tree);
		return fileErrorParseTree;
	}

	(*tree)->root = buildParseTreeResursive(file);
	fclose(file);

	if ((*tree)->root == NULL)
	{
		clearParseTree(tree);
		return outOfMemoryParseTree;
	}
	return okParseTree;
}

static int calculate(const int operand1, const int operand2, const char operation)
{
	switch (operation)
	{
	case '+':
		return operand1 + operand2;
	case '-':
		return operand1 - operand2;
	case '*':
		return operand1 * operand2;
	case '/':
		return operand1 / operand2;
	}
}

static void printTreeRecursive(const Node* const node)
{
	if (node->leftSon == NULL)
	{
		printf("%d", node->value);
		return;
	}
	printf("(");
	printTreeRecursive(node->leftSon);
	printf("%c", node->value);
	printTreeRecursive(node->rightSon);
	printf(")");
}

void printParseTree(const ParseTree* const tree)
{
	printTreeRecursive(tree->root);
}

static int calculateNodes(const Node* const node, ParseTreeError* errorCode)
{
	if (node->leftSon == NULL)
	{
		return node->value;
	}
	const int operand1 = calculateNodes(node->leftSon, errorCode);
	const int operand2 = calculateNodes(node->rightSon, errorCode);
	const char operation = (char)node->value;
	if (operation == '/' && operand2 == 0)
	{
		*errorCode = divisionByZero;
		return -1;
	}
	return calculate(operand1, operand2, operation);
}

int calculateParseTree(const ParseTree* const tree, ParseTreeError* errorCode)
{
	const int result = calculateNodes(tree->root, errorCode);
	return result;
}