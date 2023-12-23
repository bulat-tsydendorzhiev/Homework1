#include <stdio.h>
#include <string.h>

#include "phoneBook.h"

typedef struct Note
{
	char name[MAX_NAME_LENGTH];
	char phoneNumber[MAX_PHONE_NUMBER_LENGTH];
} Note;

struct PhoneBook
{
	Note notes[MAX_CONTACTS_NUMBER];
	size_t numberOfContacts;
};

PhoneBook* createPhoneBook(void)
{
	return (PhoneBook*)calloc(1, sizeof(PhoneBook));
}

ErrorCode initData(PhoneBook* const phoneBook, const char* const openningFileName)
{
	FILE* file = NULL;
	fopen_s(&file, openningFileName, "r");
	if (file == NULL)
	{
		return openFileError;
	}

	char character = getc(file);
	if ((int)character == -1)
	{
		fclose(file);
		return success;
	}
	ungetc(character, file);

	while (!feof(file) && phoneBook->numberOfContacts < MAX_CONTACTS_NUMBER)
	{
		fscanf_s(file, "%[^ ]", phoneBook->notes[phoneBook->numberOfContacts].name, MAX_NAME_LENGTH);
		fscanf_s(file, "%s\n", phoneBook->notes[phoneBook->numberOfContacts].phoneNumber, MAX_PHONE_NUMBER_LENGTH);
		++phoneBook->numberOfContacts;
	}

	fclose(file);
	return success;
}

ErrorCode addContact(PhoneBook* const phoneBook, const char name[MAX_NAME_LENGTH], const char phoneNumber[MAX_PHONE_NUMBER_LENGTH])
{
	int errorCopy = strcpy_s(phoneBook->notes[phoneBook->numberOfContacts].name, MAX_NAME_LENGTH, name);
	if (errorCopy)
	{
		return errorCopy;
	}

	errorCopy = strcpy_s(phoneBook->notes[phoneBook->numberOfContacts].phoneNumber, MAX_PHONE_NUMBER_LENGTH, phoneNumber);
	if (errorCopy)
	{
		return errorCopy;
	}

	++phoneBook->numberOfContacts;
	return success;
}

void printContacts(const PhoneBook* const phoneBook)
{
	if (phoneBook->numberOfContacts == 0)
	{
		printf("Телефонная книга пуста.\n");
		printf("\n");
		return;
	}

	printf("Список контактов:\n");
	for (size_t i = 0; i < phoneBook->numberOfContacts; ++i)
	{
		printf("%s: %s\n", phoneBook->notes[i].name, phoneBook->notes[i].phoneNumber);
	}
	printf("\n");
}

size_t* findContactsByPartOfContact(const PhoneBook* const phoneBook, const char* const partOfContact, const int choice)
{
	size_t* suitableContacts = (size_t*)calloc(MAX_CONTACTS_NUMBER + 1, sizeof(int));
	if (suitableContacts == NULL)
	{
		return NULL;
	}

	size_t j = 0;
	for (size_t i = 0; i < phoneBook->numberOfContacts; ++i)
	{
		if (choice == 3)
		{
			if (strcmp(phoneBook->notes[i].name, partOfContact) == 0)
			{
				suitableContacts[j++] = i;
			}
		}
		else if (choice == 4)
		{
			if (strcmp(phoneBook->notes[i].phoneNumber, partOfContact) == 0)
			{
				suitableContacts[j++] = i;
			}
		}
	}

	suitableContacts[j] = INT_MAX;
	return suitableContacts;
}

void printSuitableContacts(const PhoneBook* const phoneBook, const size_t* const suitableContacts, const int choice)
{
	if (suitableContacts[0] == INT_MAX)
	{
		printf("Людей с такими данными в телефонной книжке нет\n");
		printf("\n");
	}
	else
	{
		printf(choice == 4 ? "Владельцы с таким номером телефона:\n" : "Владельцы номеров телефонов с таким именем:\n");
		for (size_t i = 0; suitableContacts[i] != INT_MAX; ++i)
		{
			printf("%s: %s\n", phoneBook->notes[suitableContacts[i]].name, phoneBook->notes[suitableContacts[i]].phoneNumber);
		}
		printf("\n");
	}
}

ErrorCode saveData(const PhoneBook* const phoneBook, const char* const writtingFileName)
{
	FILE* file = NULL;
	fopen_s(&file, writtingFileName, "w");
	if (file == NULL)
	{
		return openFileError;
	}

	for (size_t i = 0; i < phoneBook->numberOfContacts; ++i)
	{
		fprintf_s(file, "%s %s\n", phoneBook->notes[i].name, phoneBook->notes[i].phoneNumber);
	}

	fclose(file);
	return success;
}

void printCommands(void)
{
	printf("Телефонный справочник\n");
	printf("Выберите одну из команд:\n");
	printf("0 - выйти\n");
	printf("1 - добавить запись (имя и телефон)\n");
	printf("2 - распечатать все имеющиеся записи\n");
	printf("3 - найти телефон по имени\n");
	printf("4 - найти имя по телефону\n");
	printf("5 - сохранить текущие данные в файл\n");

	printf("Ваша команда: ");
}

void deletePhoneBook(PhoneBook** const phoneBook)
{
	free(*phoneBook);
	*phoneBook = NULL;
}