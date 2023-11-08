#pragma once

#include <stdbool.h>

typedef enum
{
	okBST,
	keyNotFoundBST,
	outOfMemoryBST
} BinarySearchTreeErrorCode;

typedef struct BinarySearchTree BinarySearchTree;

// Создание двоичного дерева поиска
BinarySearchTree* createTree(void);

// Добавление ключа и значения в двоичное дерева поиска
BinarySearchTreeErrorCode insert(BinarySearchTree* tree, const int key, const char* const value);

// Получение значения по ключу из двоичного дерева поиска
char* getValueByKey(const BinarySearchTree* const tree, const int key);

// Поиск ключа в двоичном дереве поиска
bool findKey(const BinarySearchTree* const tree, const int key);

// Удаление узла из двоичного дерева поиска
BinarySearchTreeErrorCode deleteNode(BinarySearchTree* tree, const int key);

// Очистка двоичного дерева поиска
void clearTree(BinarySearchTree** tree);
