#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "console.h"
#include "phoneBook.h"

#define MAIN_FILE_NAME "input.txt"

static int getName(char name[MAX_NAME_LENGTH])
{
    printf("Введите имя (Не превосходящий %d символов): ", MAX_NAME_LENGTH);
    return scanf_s("%s", name, MAX_NAME_LENGTH) != 1 ? scanError : ok;
}

static int getPhoneNumber(char phoneNumber[MAX_PHONE_NUMBER_LENGTH])
{
    printf("Введите номер телефона (Не превосходящий %d символов): ", MAX_PHONE_NUMBER_LENGTH);
    return scanf_s("%s", phoneNumber, MAX_PHONE_NUMBER_LENGTH) != 1 ? scanError : ok;
}

int runProgram(void)
{
    PhoneBook phoneBook[MAX_CONTACTS_NUMBER] = { "", "" };
    size_t numberOfContacts = 0;
    const ErrorCode errorInit = initData(phoneBook, MAIN_FILE_NAME, &numberOfContacts);
    if (errorInit)
    {
        return errorInit;
    }

    while (true)
    {
        int choice = 0;
        printCommands();
        scanf_s("%d", &choice);

        switch (choice)
        {
        case exitCommand:
            return ok;
        case addContactCommand:
        {
            char name[MAX_NAME_LENGTH] = "";
            char phoneNumber[MAX_PHONE_NUMBER_LENGTH] = "";
            ConsoleError scanningError = getName(name);
            if (scanningError)
            {
                return scanningError;
            }
            scanningError = getPhoneNumber(phoneNumber);
            if (scanningError)
            {
                return scanningError;
            }
            ErrorCode addingContactError = addContact(phoneBook, name, phoneNumber, &numberOfContacts);
            if (addingContactError)
            {
                return addingContactError;
            }
            printf("Данные успешно добавлены\n");
            printf("\n");
            break;
        }
        case printContactsCommand:
            printContacts(phoneBook, numberOfContacts);
            break;
        case findPhoneNumberByNameCommand:
        {
            char name[MAX_NAME_LENGTH] = "";
            ConsoleError scanningError = getName(name);
            if (scanningError)
            {
                return scanningError;
            }

            size_t* suitableContacts = findContactsByPartOfContact(phoneBook, name, choice, numberOfContacts);
            if (suitableContacts == NULL)
            {
                return outOfMemory;
            }
            printSuitableContacts(phoneBook, suitableContacts, choice);
            free(suitableContacts);
            break;
        }
        case findNameByPhoneNumberCommand:
        {
            char phoneNumber[MAX_PHONE_NUMBER_LENGTH] = "";
            ConsoleError scanningError = getPhoneNumber(phoneNumber);
            if (scanningError)
            {
                return scanningError;
            }

            size_t* suitableContacts = findContactsByPartOfContact(phoneBook, phoneNumber, choice, numberOfContacts);
            if (suitableContacts == NULL)
            {
                return outOfMemory;
            }
            printSuitableContacts(phoneBook, suitableContacts, choice);
            free(suitableContacts);
            break;
        }
        case saveContactsCommand:
        {
            ErrorCode fileSavingError = saveData(phoneBook, MAIN_FILE_NAME, numberOfContacts);
            if (fileSavingError)
            {
                return fileSavingError;
            }
            printf("Данные успешно сохранены\n");
            printf("\n");
            break;
        }
        default:
            printf("Неизвестная команда. Попробуйте снова.\n");
            printf("\n");
            break;
        }
    }
}
