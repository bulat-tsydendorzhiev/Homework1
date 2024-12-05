#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "console.h"
#include "AVLTree.h"

#define VALUE_SIZE 100

static int getChoice(void)
{
    int choice = 0;
    scanf_s("%d", &choice);

    return choice;
}

static ConsoleError readKey(char* key)
{
    printf("������� ����: ");
    if (scanf_s("%s", key, VALUE_SIZE) != 1)
    {
        printf("�������� ����, ���������� �����\n");
        return errorInput;
    }
    return success;
}

static ConsoleError readValue(char* value)
{
    printf("������� ��������: ");
    if (scanf_s("%s", value, VALUE_SIZE) != 1)
    {
        printf("�������� ����, ���������� �����\n");
        return errorInput;
    }
    return success;
}

static ConsoleError addCommand(AVLTree* const tree, const char* const key, const char* const value)
{
    const AVLTreeError insertError = addValue(tree, key, value);
    if (insertError)
    {
        return consoleOutOfMemory;
    }

    printf("���� � �������� ���������\n");
    printf("\n");
    return success;
}

static void getCommand(AVLTree* const tree, const char* const key)
{
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

static void findCommand(AVLTree* const tree, const char* const key)
{
    const bool keyFound = contains(tree, key);
    printf(keyFound ? "����� ���� ����������\n" : "�� ���������� ������ �����\n");
    printf("\n");
}

static ConsoleError deleteCommand(AVLTree* const tree, const char* const key)
{
    const AVLTreeError errorDelete = deleteValue(tree, key);
    if (errorDelete == keyNotFound)
    {
        printf("�� ���������� ����� � ����� ���������\n");
    }
    else if (errorDelete == outOfMemoryAVL)
    {
        printf("������ ��������� ������\n");
    }
    else
    {
        printf("�������� ������ �������\n");
    }
    printf("\n");

    return errorDelete == outOfMemoryAVL ? consoleOutOfMemory : success;
}

ConsoleError runProgram(void)
{
    AVLTree* tree = createAVLTree();
    if (tree == NULL)
    {
        return consoleOutOfMemory;
    }

    while (true)
    {
        printCommands();

        const int choice = getChoice();
        printf((choice != 0) ? "-----------------------------------------------------------------\n" : "");
        switch (choice)
        {
        case quit:
            deleteTree(&tree);
            return success;
        case add:
        {
            char key[VALUE_SIZE] = "";
            char value[VALUE_SIZE] = "";
            if (readKey(key) == errorInput)
            {
                break;
            }
            if (readValue(value) == errorInput)
            {
                break;
            }

            const ConsoleError errorAddCommand = addCommand(tree, key, value);
            if (errorAddCommand)
            {
                deleteTree(&tree);
                return errorAddCommand;
            }
            break;
        }
        case get:
        {
            char key[VALUE_SIZE] = "";
            if (readKey(key) == errorInput)
            {
                break;
            }

            getCommand(tree, key);
            break;
        }
        case find:
        {
            char key[VALUE_SIZE] = "";
            if (readKey(key) == errorInput)
            {
                break;
            }

            findCommand(tree, key);
            break;
        }
        case delete:
        {
            char key[VALUE_SIZE] = "";
            if (readKey(key) == errorInput)
            {
                break;
            }

            const ConsoleError errorDelete = deleteCommand(tree, key);
            if (errorDelete)
            {
                deleteTree(&tree);
                return errorDelete;
            }
            break;
        }
        default:
            printf("����������� �������. ���������� �����\n");
            printf("-----------------------------------------------------------------\n");
            break;
        }
    }
}
