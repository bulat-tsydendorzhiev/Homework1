#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tests.h"
#include "phoneBook.h"

#define EMPTY_FILE_NAME "testFile1.txt"
#define NOT_EMPTY_FILE_NAME "testFile2.txt"

static PhoneBook* initTestPhoneBook(const char* const testFileName)
{
    PhoneBook* phoneBook = createPhoneBook();
    if (phoneBook == NULL)
    {
        return NULL;
    }

    const int errorInit = initData(phoneBook, testFileName);
    if (errorInit)
    {
        free(phoneBook);
        return NULL;
    }

    return phoneBook;
}

static bool runDataInitTest(void)
{
    PhoneBook* phoneBook = initTestPhoneBook(EMPTY_FILE_NAME);
    if (phoneBook == NULL)
    {
        return false;
    }
    deletePhoneBook(&phoneBook);
    return true;
}

static size_t findIndexOfContact(const size_t* const contacts)
{
    size_t indexOfContact = INT_MAX;
    for (size_t i = 0; contacts[i] != INT_MAX; i++)
    {
        indexOfContact = contacts[i];
    }
    return indexOfContact;
}

static bool runFindingContactsTestForEmptyFile(void)
{
    PhoneBook* phoneBook = initTestPhoneBook(EMPTY_FILE_NAME);
    if (phoneBook == NULL)
    {
        return false;
    }

    size_t* contacts = findContactsByPartOfContact(phoneBook, "Me", 3);
    if (contacts == NULL)
    {
        deletePhoneBook(&phoneBook);
        return false;
    }

    const size_t indexOfContact = findIndexOfContact(contacts);

    free(contacts);
    deletePhoneBook(&phoneBook);
    return indexOfContact == INT_MAX;
}

static bool runFindingContactsTestForNotEmptyFile(void)
{
    PhoneBook* phoneBook = initTestPhoneBook(NOT_EMPTY_FILE_NAME);
    if (phoneBook == NULL)
    {
        return false;
    }

    size_t* contacts = findContactsByPartOfContact(phoneBook, "7890", 4);
    if (contacts == NULL)
    {
        deletePhoneBook(&phoneBook);
        return false;
    }

    const size_t indexOfContact = findIndexOfContact(contacts);

    free(contacts);
    deletePhoneBook(&phoneBook);
    return indexOfContact == 2;
}

static bool runFindingContactsTest(void)
{
    return runFindingContactsTestForEmptyFile() && runFindingContactsTestForNotEmptyFile();
}

static bool runAddingContactTest(void)
{
    PhoneBook* phoneBook = initTestPhoneBook(NOT_EMPTY_FILE_NAME);
    if (phoneBook == NULL)
    {
        return false;
    }

    const ErrorCode errorAdding = addContact(phoneBook, "Cat", "0000");
    if (errorAdding)
    {
        deletePhoneBook(&phoneBook);
        return false;
    }

    size_t* contacts = findContactsByPartOfContact(phoneBook, "Cat", 3);
    if (contacts == NULL)
    {
        deletePhoneBook(&phoneBook);
        return false;
    }

    const size_t indexOfContact = findIndexOfContact(contacts);

    free(contacts);
    deletePhoneBook(&phoneBook);
    return indexOfContact == 3;
}

static bool runSavingDataTest(void)
{
    PhoneBook* phoneBook = initTestPhoneBook(NOT_EMPTY_FILE_NAME);
    if (phoneBook == NULL)
    {
        return false;
    }

    const ErrorCode errorAdding = addContact(phoneBook, "Cat", "0000");
    if (errorAdding)
    {
        deletePhoneBook(&phoneBook);
        return false;
    }

    const ErrorCode errorSave = saveData(phoneBook, "outputFileForTest.txt");
    if (errorSave)
    {
        deletePhoneBook(&phoneBook);
        return false;
    }

    const char expectedData[][2][6] = { {"John", "1234"},
                                        {"Me", "4567"}, 
                                        {"Fabio", "7890"}, 
                                        {"Cat", "0000"} };

    FILE* file = NULL;
    fopen_s(&file, "outputFileForTest.txt", "r");
    if (file == NULL)
    {
        deletePhoneBook(&phoneBook);
        return false;
    }

    size_t i = 0;
    while (!feof(file))
    {
        char name[MAX_NAME_LENGTH] = "";
        char phoneNumber[MAX_PHONE_NUMBER_LENGTH] = "";
        if (fscanf_s(file, "%[^ ]", name, MAX_NAME_LENGTH) != 1 || fscanf_s(file, "%s\n", phoneNumber, MAX_PHONE_NUMBER_LENGTH) != 1)
        {
            deletePhoneBook(&phoneBook);
            fclose(file);
            return false;
        }

        if (strcmp(name, expectedData[i][0]) != 0 || strcmp(phoneNumber, expectedData[i][1]) != 0)
        {
            deletePhoneBook(&phoneBook);
            fclose(file);
            return false;
        }
        ++i;
    }

    deletePhoneBook(&phoneBook);
    fclose(file);
    return true;
}

bool runTests(void)
{
    if (!runDataInitTest())
    {
        printf("Тест инициализации данных провалился\n");
        return false;
    }
    if (!runFindingContactsTest())
    {
        printf("Тест поиска контакта провалился\n");
        return false;
    }
    if (!runAddingContactTest())
    {
        printf("Тест добавления контакта провалился\n");
        return false;
    }
    if (!runSavingDataTest())
    {
        printf("Тест сохранения данных провалился\n");
        return false;
    }
    return true;
}
