#include <stdlib.h>
#include <stdio.h>

#include "commandsAVLTree.h"
#include "AVLTree.h"

#define VALUE_SIZE 100

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

static CommandError readKey(char* key)
{
    printf("Введите ключ: ");
    if (scanf_s("%s", key, VALUE_SIZE) != 1)
    {
        printf("Неверный ввод, попробуйте снова\n");
        return errorInput;
    }
    return successfullCommand;
}

static CommandError readValue(char* value)
{
    printf("Введите значение: ");
    if (scanf_s("%s", value, VALUE_SIZE) != 1)
    {
        printf("Неверный ввод, попробуйте снова\n");
        return errorInput;
    }
    return successfullCommand;
}

static CommandError addCommand(AVLTree* const tree, const char* const key, const char* const value)
{
    const AVLTreeError insertError = addValue(tree, key, value);
    if (insertError)
    {
        return outOfMemoryCommands;
    }

    printf("Ключ и значение добавлены\n");
    printf("\n");
    return successfullCommand;
}

static void getCommand(AVLTree* const tree, const char* const key)
{
    const char* value = getValueByKey(tree, key);
    if (value == NULL)
    {
        printf("Не существует значения с таким ключом\n");
    }
    else
    {
        printf("Значение: %s\n", value);
    }
    printf("\n");
}

static void findCommand(AVLTree* const tree, const char* const key)
{
    const bool keyFound = contains(tree, key);
    if (!keyFound)
    {
        printf("Не существует такого ключа\n");
    }
    else
    {
        printf("Такой ключ существует\n");
    }
    printf("\n");
}

static CommandError deleteCommand(AVLTree* const tree, const char* const key)
{
    const AVLTreeError errorDelete = deleteValue(tree, key);
    if (errorDelete == keyNotFound)
    {
        printf("Не существует ключа с таким значением\n");
    }
    else if (errorDelete == outOfMemoryAVL)
    {
        printf("Ошибка выделения памяти\n");
    }
    else
    {
        printf("Удаление прошло успешно\n");
    }
    printf("\n");

    return errorDelete;
}

CommandError commands(void)
{
    AVLTree* tree = createAVLTree();
    if (tree == NULL)
    {
        return outOfMemoryCommands;
    }

    CommandError error = successfullCommand;
    bool endOfProgram = false;
    while (!endOfProgram)
    {
        char key[VALUE_SIZE] = "";
        char value[VALUE_SIZE] = "";
        printComands();

        const int choice = getChoice();
        printf((choice != 0) ? "-----------------------------------------------------------------\n" : "");
        switch (choice)
        {
        case quit:
            endOfProgram = true;
            break;
        case add:
            if (readKey(key) == errorInput)
            {
                break;
            }
            if (readValue(value) == errorInput)
            {
                break;
            }
            error = addCommand(tree, key, value);
            break;
        case get:
            if (readKey(key) == errorInput)
            {
                break;
            }
            getCommand(tree, key);
            break;
        case find:
            if (readKey(key) == errorInput)
            {
                break;
            }
            findCommand(tree, key);
            break;
        case delete:
            if (readKey(key) == errorInput)
            {
                break;
            }
            error = deleteCommand(tree, key);
            break;
        default:
            printf("Неизвестная команда. Попробуйте снова\n");
            printf("-----------------------------------------------------------------\n");
            break;
        }

        if (error == outOfMemoryAVL)
        {
            deleteTree(&tree);
            return error;
        }
    }

    deleteTree(&tree);
    return successfullCommand;
}
