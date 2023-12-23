#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "console.h"
#include "phoneBook.h"

#define MAIN_FILE "input.txt"

typedef enum
{
	exitCommand,
	addNoteCommand,
	printContactsCommand,
	findPhoneNumberByNameCommand,
	findNameByPhoneNumberCommand,
	saveNotesCommand
} Command;

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
	PhoneBook* phoneBook = createPhoneBook();
	if (phoneBook == NULL)
	{
		return outOfMemory;
	}

	const int errorInit = initData(phoneBook, MAIN_FILE);
	if (errorInit)
	{
		free(phoneBook);
		return errorInit;
	}

	while (true)
	{
		int choice = 0;
		printCommands();
		scanf_s("%d", &choice);

		size_t* suitableContacts = NULL;
		ErrorCode error = 0;
		char name[MAX_NAME_LENGTH] = "";
		char phoneNumber[MAX_PHONE_NUMBER_LENGTH] = "";
		switch (choice)
		{
		case exitCommand:
			deletePhoneBook(&phoneBook);
			return ok;
		case addNoteCommand:
			error = getName(name);
			if (error)
			{
				deletePhoneBook(&phoneBook);
				return error;
			}
			error = getPhoneNumber(phoneNumber);
			if (error)
			{
				deletePhoneBook(&phoneBook);
				return error;
			}
			error = addContact(phoneBook, name, phoneNumber);
			if (error)
			{
				deletePhoneBook(&phoneBook);
				return error;
			}
			printf("Данные успешно добавлены\n");
			printf("\n");
			break;
		case printContactsCommand:
			printContacts(phoneBook);
			break;
		case findPhoneNumberByNameCommand:
			error = getName(name);
			if (error)
			{
				deletePhoneBook(&phoneBook);
				return error;
			}
			suitableContacts = findContactsByPartOfContact(phoneBook, name, choice);
			if (suitableContacts == NULL)
			{
				deletePhoneBook(&phoneBook);
				free(suitableContacts);
				return outOfMemory;
			}
			printSuitableContacts(phoneBook, suitableContacts, choice);
			break;
		case findNameByPhoneNumberCommand:
			error = getPhoneNumber(phoneNumber);
			if (error)
			{
				deletePhoneBook(&phoneBook);
				return error;
			}
			suitableContacts = findContactsByPartOfContact(phoneBook, phoneNumber, choice);
			if (suitableContacts == NULL)
			{
				deletePhoneBook(&phoneBook);
				free(suitableContacts);
				return outOfMemory;
			}
			printSuitableContacts(phoneBook, suitableContacts, choice);
			break;
		case saveNotesCommand:
			error = saveData(phoneBook, MAIN_FILE);
			if (error)
			{
				deletePhoneBook(&phoneBook);
				return error;
			}
			printf("Данные успешно сохранены\n");
			printf("\n");
			break;
		default:
			printf("Неизвестная команда. Попробуйте снова.\n");
			printf("\n");
			break;
		}
	}
}
