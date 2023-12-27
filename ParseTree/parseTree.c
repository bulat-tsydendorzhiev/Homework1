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

static Node* buildParseTreeResursive(FILE* const file, ParseTreeError* const errorCode)
{
    Node* node = NULL;
    char symbol = ' ';
    while (symbol != ')' && !feof(file))
    {
        symbol = fgetc(file);
        const char nextSymbol = fgetc(file);
        const bool nextSymbolIsDigit = isDigit(nextSymbol);
        ungetc(nextSymbol, file);
        if (isDigit(symbol) || (isOperation(symbol) && nextSymbolIsDigit))
        {
            ungetc(symbol, file);
            int number = 0;
            const int amountOfScannedElements = fscanf_s(file, "%d", &number);
            if (amountOfScannedElements != 1)
            {
                *errorCode = scanningError;
                return NULL;
            }

            node = createNode(number);
            if (node == NULL)
            {
                *errorCode = outOfMemoryParseTree;
                return NULL;
            }
            return node;
        }
        else if (isOperation(symbol))
        {
            node = createNode((int)symbol);
            if (node == NULL)
            {
                *errorCode = outOfMemoryParseTree;
                return NULL;
            }

            node->leftSon = buildParseTreeResursive(file, errorCode);
            node->rightSon = buildParseTreeResursive(file, errorCode);
            if (node->leftSon == NULL || node->rightSon == NULL)
            {
                *errorCode = outOfMemoryParseTree;
                clearNodes(node->leftSon);
                clearNodes(node->rightSon);
                return NULL;
            }
        }
    }
    return node;
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
        return fileErrorParseTree;
    }

    ParseTreeError errorBuild = okParseTree;
    (*tree)->root = buildParseTreeResursive(file, &errorBuild);
    fclose(file);

    if ((*tree)->root == NULL)
    {
        return errorBuild;
    }
    return okParseTree;
}

static int calculate(const int operand1, const int operand2, const char operation, ParseTreeError* const errorCode)
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
        if (operand2 == 0)
        {
            *errorCode = divisionByZero;
            return divisionByZero;
        }
        return operand1 / operand2;
    default:
        *errorCode = unknownSymbol;
        return unknownSymbol;
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

static int calculateNodes(const Node* const node, ParseTreeError* const errorCode)
{
    if (*errorCode)
    {
        return *errorCode;
    }
    if (node->leftSon == NULL)
    {
        return node->value;
    }

    const int operand1 = calculateNodes(node->leftSon, errorCode);
    const int operand2 = calculateNodes(node->rightSon, errorCode);
    const char operation = (char)node->value;
    return calculate(operand1, operand2, operation, errorCode);
}

int calculateParseTree(const ParseTree* const tree, ParseTreeError* const errorCode)
{
    const int result = calculateNodes(tree->root, errorCode);
    return result;
}