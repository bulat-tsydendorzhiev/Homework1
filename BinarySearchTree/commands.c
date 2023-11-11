#include <stdlib.h>
#include <stdio.h>

#include "commands.h"
#include "BinarySearchTree.h"

enum command
{
    quit,
    add,
    get,
    find,
    delete,
};

static void printComands(void)
{
    printf("Выберите одну из следующих команд:\n");
    printf("0 - Выйти\n");
    printf("1 - Добавить значение по заданному ключу в словарь.\n");
    printf("2 - Получить значение по заданному ключу из словаря.\n");
    printf("3 - Проверить наличие заданного ключа в словаре.\n");
    printf("4 - Удалить заданный ключ и связанное с ним значение из словаря.\n");
    printf("Ваш выбор: ");
}

static int getChoice(void)
{
    int choice = 0;
    scanf_s("%d", &choice);

    return choice;
}

static char* getValue(int* length)
{
    printf("Введите значение: ");
    *length = 0;
    size_t capacity = 1;
    char* string = (char*)malloc(sizeof(char));
    if (string == NULL)
    {
        return NULL;
    }

    char symbol = getchar();

    while (symbol != '\n')
    {
        if (*length >= capacity)
        {
            capacity *= 2;
            const char* newString = (char*)realloc(string, capacity * sizeof(char));
            if (newString == NULL)
            {
                return NULL;
            }

            string = newString;
        }

        string[(*length)] = symbol;
        (*length)++;

        symbol = getchar();
    }

    string[*length] = '\0';

    return string;
}

static int getKey(void)
{
    int key = 0;
    printf("Введите ключ: ");
    scanf_s("%d", &key);
    return key;
}

static comandError addCommand(BinarySearchTree* const tree)
{
    const int key = getKey();

    getchar();
    int length = 0;
    const char* value = getValue(&length);
    if (value == NULL)
    {
        return outOfMemoryCommands;
    }

    const BinarySearchTreeErrorCode insertError = insert(tree, key, value);
    if (insertError)
    {
        return outOfMemoryCommands;
    }

    printf("Ключ и значение добавлены\n");
    printf("\n");
    return successfullCommand;
}

static void getCommand(BinarySearchTree* const tree)
{
    const int key = getKey();

    const char* value = getValueByKey(tree, key);
    if (value == NULL)
    {
        printf("Не существует значения с таким ключом\n");
    }
    else
    {
        printf("Значение: %s\n", value);
    }
}

static void findCommand(BinarySearchTree* const tree)
{
    const int key = getKey();

    const bool keyNotFound = findKey(tree, key);
    if (keyNotFound)
    {
        printf("Не существует такого ключа\n");
    }
    else
    {
        printf("Такой ключ существует\n");
    }
}

static void deleteCommand(BinarySearchTree* const tree)
{
    const int key = getKey();

    const BinarySearchTreeErrorCode errorDelete = deleteNode(tree, key);
    if (errorDelete == keyNotFoundBST)
    {
        printf("Не существует ключа с таким значением\n");
    }
    else
    {
        printf("Удаление прошло успешно\n");
    }
    printf("\n");
}

comandError commands(void)
{
    BinarySearchTree* tree = createTree();
    if (tree == NULL)
    {
        return outOfMemoryCommands;
    }

    comandError error = 0;
    while (true)
    {
        printComands();

        int choice = getChoice();
        printf((choice != 0) ? "-----------------------------------------------------------------\n" : "");

        switch (choice)
        {
        case quit:
            clearTree(&tree);
            return successfullCommand;
        case add:
            error = addCommand(tree);
            break;
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
            printf("Неизвестная команда. Попробуйте снова\n");
            printf("-----------------------------------------------------------------\n");
            break;
        }

        if (error)
        {
            clearTree(&tree);
            return error;
        }
    }
}
