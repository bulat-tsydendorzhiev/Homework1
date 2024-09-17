#include <stdio.h>
#include <string.h>

#include "phoneBook.h"

ErrorCode initData(PhoneBook phoneBook[MAX_CONTACTS_NUMBER], const char* const fileNameToOpen, size_t* const numberOfContacts)
{
    FILE* file = NULL;
    fopen_s(&file, fileNameToOpen, "r");
    if (file == NULL)
    {
        return openFileError;
    }

    // Check file on emptiness
    char character = getc(file);
    if ((int)character == -1)
    {
        fclose(file);
        return success;
    }
    ungetc(character, file);

    while (!feof(file) && *numberOfContacts < MAX_CONTACTS_NUMBER)
    {
        if (fscanf_s(file, "%[^ ]", phoneBook[*numberOfContacts].name, MAX_NAME_LENGTH) == 1 &&
            fscanf_s(file, "%s\n", phoneBook[*numberOfContacts].phoneNumber, MAX_PHONE_NUMBER_LENGTH) == 1)
        {
            ++(*numberOfContacts);
        }
    }

    fclose(file);
    return success;
}

ErrorCode addContact(PhoneBook phoneBook[MAX_CONTACTS_NUMBER], const char name[MAX_NAME_LENGTH], const char phoneNumber[MAX_PHONE_NUMBER_LENGTH],
    size_t* const numberOfContacts)
{
    int errorCopy = strcpy_s(phoneBook[*numberOfContacts].name, MAX_NAME_LENGTH, name);
    if (errorCopy)
    {
        return copyError;
    }

    errorCopy = strcpy_s(phoneBook[*numberOfContacts].phoneNumber, MAX_PHONE_NUMBER_LENGTH, phoneNumber);
    if (errorCopy)
    {
        return copyError;
    }

    ++(*numberOfContacts);
    return success;
}

void printContacts(const PhoneBook phoneBook[MAX_CONTACTS_NUMBER], const size_t numberOfContacts)
{
    if (numberOfContacts == 0)
    {
        printf("���������� ����� �����.\n");
        printf("\n");
        return;
    }

    printf("������ ���������:\n");
    for (size_t i = 0; i < numberOfContacts; ++i)
    {
        printf("%s: %s\n", phoneBook[i].name, phoneBook[i].phoneNumber);
    }
    printf("\n");
}

size_t* findContactsByPartOfContact(const PhoneBook phoneBook[MAX_CONTACTS_NUMBER], const char* const partOfContact, const int choice, const size_t numberOfContacts)
{
    size_t* suitableContacts = (size_t*)calloc(MAX_CONTACTS_NUMBER + 1, sizeof(int));
    if (suitableContacts == NULL)
    {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < numberOfContacts; ++i)
    {
        if (choice == findPhoneNumberByNameCommand)
        {
            if (strcmp(phoneBook[i].name, partOfContact) == 0)
            {
                suitableContacts[j] = i;
                ++j;
            }
        }
        else if (choice == findNameByPhoneNumberCommand)
        {
            if (strcmp(phoneBook[i].phoneNumber, partOfContact) == 0)
            {
                suitableContacts[j] = i;
                ++j;
            }
        }
    }

    suitableContacts[j] = BREAK_POINT;
    return suitableContacts;
}

void printSuitableContacts(const PhoneBook phoneBook[MAX_CONTACTS_NUMBER], const size_t* const suitableContacts, const int choice)
{
    if (suitableContacts[0] == BREAK_POINT)
    {
        printf("����� � ������ ������� � ���������� ������ ���\n");
        printf("\n");
        return;
    }

    printf(choice == findNameByPhoneNumberCommand ? "��������� � ����� ������� ��������:\n" : "��������� ������� ��������� � ����� ������:\n");
    for (size_t i = 0; suitableContacts[i] != BREAK_POINT; ++i)
    {
        printf("%s: %s\n", phoneBook[suitableContacts[i]].name, phoneBook[suitableContacts[i]].phoneNumber);
    }
    printf("\n");
}

ErrorCode saveData(const PhoneBook phoneBook[MAX_CONTACTS_NUMBER], const char* const fileNameToWrite, const size_t numberOfContacts)
{
    FILE* file = NULL;
    fopen_s(&file, fileNameToWrite, "w");
    if (file == NULL)
    {
        return openFileError;
    }

    for (size_t i = 0; i < numberOfContacts; ++i)
    {
        fprintf_s(file, "%s %s\n", phoneBook[i].name, phoneBook[i].phoneNumber);
    }

    fclose(file);
    return success;
}

void printCommands(void)
{
    printf("���������� ����������\n");
    printf("�������� ���� �� ������:\n");
    printf("0 - �����\n");
    printf("1 - �������� ������ (��� � �������)\n");
    printf("2 - ����������� ��� ��������� ������\n");
    printf("3 - ����� ������� �� �����\n");
    printf("4 - ����� ��� �� ��������\n");
    printf("5 - ��������� ������� ������ � ����\n");

    printf("���� �������: ");
}
