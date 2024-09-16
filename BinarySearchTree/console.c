#include <stdlib.h>
#include <stdio.h>

#include "console.h"
#include "BinarySearchTree.h"

static int getChoice(void)
{
    int choice = 0;
    scanf_s("%d", &choice);
    return choice;
}

static char* getValue(void)
{
    printf("������� ��������: ");
    size_t length = 0;
    size_t capacity = 1;
    char* string = (char*)calloc(1, sizeof(char));
    if (string == NULL)
    {
        return NULL;
    }

    char character = getchar();
    while (character != '\n')
    {
        string[length] = character;
        ++length;
        if (length >= capacity)
        {
            const char* temp = (char*)realloc(string, 2 * capacity * sizeof(char));
            if (temp == NULL)
            {
                return NULL;
            }
            capacity *= 2;
            string = temp;
        }

        character = getchar();
    }
    string[length] = '\0';

    return string;
}

static int getKey(void)
{
    int key = 0;
    printf("������� ����: ");
    scanf_s("%d", &key);
    return key;
}

static ConsoleError addCommand(BinarySearchTree* const tree)
{
    const int key = getKey();

    const int character = getchar(); // in order to start getting value
    const char* value = getValue();
    if (value == NULL)
    {
        return lackOfMemory;
    }

    const BinarySearchTreeErrorCode insertError = insert(tree, key, value);
    if (insertError)
    {
        return lackOfMemory;
    }

    printf("���� � �������� ���������\n");
    printf("\n");
    return success;
}

static void getCommand(BinarySearchTree* const tree)
{
    const int key = getKey();
    const char* value = getValueByKey(tree, key);
    if (value == NULL)
    {
        printf("�� ���������� �������� � ����� ������\n");
    }
    else
    {
        printf("��������: %s\n", value);
    }
    printf("\n");
}

static void findCommand(BinarySearchTree* const tree)
{
    const int key = getKey();
    const bool keyFound = findKey(tree, key);
    printf(keyFound ? "����� ���� ����������\n": "�� ���������� ������ �����\n");
    printf("\n");
}

static void deleteCommand(BinarySearchTree* const tree)
{
    const int key = getKey();
    const BinarySearchTreeErrorCode errorDelete = deleteNode(tree, key);
    printf(errorDelete == keyNotFoundBST ? "�� ���������� ����� � ����� ���������\n": "�������� ������ �������\n");
    printf("\n");
}

ConsoleError runProgram(void)
{
    BinarySearchTree* tree = createTree();
    if (tree == NULL)
    {
        printf("������ ��������� ������");
        return lackOfMemory;
    }

    while (true)
    {
        printCommands();

        const int choice = getChoice();
        printf((choice != 0) ? "-----------------------------------------------------------------\n" : "");

        switch (choice)
        {
        case quit:
            clearTree(&tree);
            return success;
        case add:
        {
            const ConsoleError errorAdding = addCommand(tree);
            if (errorAdding)
            {
                clearTree(&tree);
                printf("������ ��������� ������");
                return lackOfMemory;
            }
            break;
        }
        case get:
            getCommand(tree);
            break;
        case find:
            findCommand(tree);
            break;
        case delete:
            deleteCommand(tree);
            break;
        default:
            printf("����������� �������. ���������� �����\n");
            printf("-----------------------------------------------------------------\n");
            break;
        }
    }
}
