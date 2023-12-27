#pragma once

#include <stdbool.h>

typedef enum
{
    okParseTree,
    scanningError,
    outOfMemoryParseTree,
    fileErrorParseTree,
    divisionByZero,
    unknownSymbol
} ParseTreeError;

typedef struct ParseTree ParseTree;

// Create parse tree
ParseTree* createParseTree(void);

// Clear parse tree
void clearParseTree(ParseTree** tree);

// Build tree using the file
ParseTreeError buildParseTree(ParseTree** tree, const char* const filename);

// Print parse tree
void printParseTree(const ParseTree* const tree);

// Calculate the value of parse tree
int calculateParseTree(const ParseTree* const tree, ParseTreeError* errorCode);
