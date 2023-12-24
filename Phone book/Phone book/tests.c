#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tests.h"
#include "phoneBook.h"

#define EMPTY_FILE_NAME "testFile1.txt"
#define NOT_EMPTY_FILE_NAME "testFile2.txt"

static bool runDataInitTestForEmptyFile(void)
{
    PhoneBook phoneBook[MAX_CONTACTS_NUMBER] = { "", "" };
    size_t numberOfContacts = 0;
    const ErrorCode errorInit = initData(phoneBook, EMPTY_FILE_NAME, &numberOfContacts);
    if (errorInit)
    {
        return false;
    }

    return numberOfContacts == 0;
}

static bool runDataInitTestForNotEmptyFile(void)
{
    PhoneBook phoneBook[MAX_CONTACTS_NUMBER] = { "", "" };
    size_t numberOfContacts = 0;
    const ErrorCode errorInit = initData(phoneBook, NOT_EMPTY_FILE_NAME, &numberOfContacts);
    if (errorInit)
    {
        return false;
    }

    return numberOfContacts == 3;
}

static bool runDataInitTest(void)
{
    return runDataInitTestForEmptyFile() && runDataInitTestForNotEmptyFile();
}

static size_t findIndexOfContact(const size_t* const contacts)
{
    size_t indexOfContact = BREAK_POINT;
    for (size_t i = 0; contacts[i] != BREAK_POINT; i++)
    {
        indexOfContact = contacts[i];
    }
    return indexOfContact;
}

static bool runFindingContactsTestForEmptyFile(void)
{
    PhoneBook phoneBook[MAX_CONTACTS_NUMBER] = { "", "" };
    size_t numberOfContacts = 0;
    const ErrorCode errorInit = initData(phoneBook, EMPTY_FILE_NAME, &numberOfContacts);
    if (errorInit)
    {
        return false;
    }

    size_t* contacts = findContactsByPartOfContact(phoneBook, "Me", findPhoneNumberByNameCommand, numberOfContacts);
    if (contacts == NULL)
    {
        return false;
    }

    const size_t indexOfContact = findIndexOfContact(contacts);

    free(contacts);
    return indexOfContact == BREAK_POINT;
}

static bool runFindingContactsTestForNotEmptyFile(void)
{
    PhoneBook phoneBook[MAX_CONTACTS_NUMBER] = { "", "" };
    size_t numberOfContacts = 0;
    const ErrorCode errorInit = initData(phoneBook, NOT_EMPTY_FILE_NAME, &numberOfContacts);
    if (errorInit)
    {
        return false;
    }

    size_t* contacts = findContactsByPartOfContact(phoneBook, "7890", findNameByPhoneNumberCommand, numberOfContacts);
    if (contacts == NULL)
    {
        return false;
    }

    const size_t indexOfContact = findIndexOfContact(contacts);

    free(contacts);
    return indexOfContact == 2;
}

static bool runFindingContactsTest(void)
{
    return runFindingContactsTestForEmptyFile() && runFindingContactsTestForNotEmptyFile();
}

static bool runAddingContactTest(void)
{
    PhoneBook phoneBook[MAX_CONTACTS_NUMBER] = { "", "" };
    size_t numberOfContacts = 0;
    const ErrorCode errorInit = initData(phoneBook, NOT_EMPTY_FILE_NAME, &numberOfContacts);
    if (errorInit)
    {
        return false;
    }

    const ErrorCode errorAdding = addContact(phoneBook, "Cat", "0000", &numberOfContacts);
    if (errorAdding)
    {
        return false;
    }

    size_t* contacts = findContactsByPartOfContact(phoneBook, "Cat", findPhoneNumberByNameCommand, numberOfContacts);
    if (contacts == NULL)
    {
        return false;
    }

    const size_t indexOfContact = findIndexOfContact(contacts);
    free(contacts);
    return indexOfContact == 3;
}

static bool runSavingDataTest(void)
{
    PhoneBook phoneBook[MAX_CONTACTS_NUMBER] = { "", "" };
    size_t numberOfContacts = 0;
    const ErrorCode errorInit = initData(phoneBook, NOT_EMPTY_FILE_NAME, &numberOfContacts);
    if (errorInit)
    {
        return false;
    }

    const ErrorCode errorAdding = addContact(phoneBook, "Cat", "0000", &numberOfContacts);
    if (errorAdding)
    {
        return false;
    }

    const ErrorCode errorSave = saveData(phoneBook, "outputFileForTest.txt", numberOfContacts);
    if (errorSave)
    {
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
        return false;
    }

    for (size_t i = 0; !feof(file); ++i)
    {
        char name[MAX_NAME_LENGTH] = "";
        char phoneNumber[MAX_PHONE_NUMBER_LENGTH] = "";
        if (fscanf_s(file, "%[^ ]", name, MAX_NAME_LENGTH) != 1 || fscanf_s(file, "%s\n", phoneNumber, MAX_PHONE_NUMBER_LENGTH) != 1)
        {
            fclose(file);
            return false;
        }

        if (strcmp(name, expectedData[i][0]) != 0 || strcmp(phoneNumber, expectedData[i][1]) != 0)
        {
            fclose(file);
            return false;
        }
    }

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
