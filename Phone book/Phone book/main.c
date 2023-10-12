#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PHONE_NUMBER_LENGTH 20
#define MAX_CONTACTS 100

typedef struct
{
	char name[MAX_NAME_LENGTH];
	char phoneNumber[MAX_PHONE_NUMBER_LENGTH];
} PhoneBook;

int loadData(PhoneBook* phoneBook, int* numberOfContacts)
{
	FILE* file;
	fopen_s(&file, "PhoneBookFile.txt", "r");
	if (file == NULL)
	{
		return 1;
	}

	while (!feof(file) && *numberOfContacts < 100)
	{
		char name[MAX_NAME_LENGTH], phoneNumber[MAX_PHONE_NUMBER_LENGTH];
		fscanf_s(file, "%[^ ]", name, MAX_NAME_LENGTH);
		fscanf_s(file, "%s\n", phoneNumber, MAX_PHONE_NUMBER_LENGTH);

		strncpy_s(phoneBook[*numberOfContacts].name, MAX_NAME_LENGTH + 1, name, MAX_NAME_LENGTH);
		strncpy_s(phoneBook[*numberOfContacts].phoneNumber, MAX_PHONE_NUMBER_LENGTH + 1, phoneNumber, MAX_PHONE_NUMBER_LENGTH);
		++*numberOfContacts;
	}

	fclose(file);
	return 0;
}

void addContact(PhoneBook* phoneBook, int* numberOfContacts)
{
	char name[MAX_NAME_LENGTH], phoneNumber[MAX_PHONE_NUMBER_LENGTH];
	printf("Введите имя: ");
	scanf_s("%s", name, MAX_NAME_LENGTH);
	printf("Введите номер: ");
	scanf_s("%s", phoneNumber, MAX_PHONE_NUMBER_LENGTH);

	strcpy_s(phoneBook[*numberOfContacts].name, sizeof(char) * MAX_NAME_LENGTH, name);
	strcpy_s(phoneBook[*numberOfContacts].phoneNumber, sizeof(char) * MAX_PHONE_NUMBER_LENGTH, phoneNumber);

	++*numberOfContacts;
	printf("\n");
}

void printContacts(PhoneBook* phoneBook, int numberOfContacts) {
	if (numberOfContacts == 0) {
		printf("Телефонная книга пуста.\n");
		return;
	}
	printf("Список контактов:\n");
	for (int i = 0; i < numberOfContacts; i++) {
		printf("%s: %s\n", phoneBook[i].name, phoneBook[i].phoneNumber);
	}
	printf("\n");
}

void findPhoneNumber(PhoneBook* phoneBook, int numberOfContacts)
{
	// Проверяем телефонную книжку на пустоту
	if (numberOfContacts == 0) {
		printf("Телефонная книга пуста.\n");
		return;
	}

	// Вводим имя владельца
	char name[MAX_NAME_LENGTH];
	printf("Введите имя владельца: ");
	scanf_s("%s", name, MAX_NAME_LENGTH);

	for (int i = 0; i < numberOfContacts; ++i)
	{
		if (strcmp(phoneBook[i].name, name) == 0) // нашелся владелец телефона с таким именем
		{
			printf("%s: %s\n", phoneBook[i].name, phoneBook[i].phoneNumber);
		}
	}
	printf("\n");
}

void findName(PhoneBook* phoneBook, int numberOfContacts)
{
	// Проверяем телефонную книжку на пустоту
	if (numberOfContacts == 0) {
		printf("Телефонная книга пуста.\n");
		return;
	}

	// Вводим номер телефона владельца
	char phoneNumber[MAX_PHONE_NUMBER_LENGTH];
	printf("Введите номер телефона: ");
	scanf_s("%s", phoneNumber, MAX_PHONE_NUMBER_LENGTH);

	for (int i = 0; i < numberOfContacts; ++i)
	{
		if (strcmp(phoneBook[i].phoneNumber, phoneNumber) == 0) // нашелся владелец телефона с таким номером
		{
			printf("%s: %s\n", phoneBook[i].name, phoneBook[i].phoneNumber);
		}
	}
	printf("\n");
}

int saveData(PhoneBook* phoneBook, int numberOfContacts)
{
	FILE* file;
	fopen_s(&file, "PhoneBookFile.txt", "w");
	if (file == NULL)
	{
		return 1;
	}

	for (int i = 0; i < numberOfContacts; ++i)
	{
		fprintf_s(file, "%s %s\n", phoneBook[i].name, phoneBook[i].phoneNumber);
	}

	fclose(file);
	return 0;
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

int tests()
{

}

int main()
{
	system("chcp 1251 > nul");
	PhoneBook phoneBook[MAX_CONTACTS];
	int numberOfContacts = 0;

	const int errorOpenFile = loadData(&phoneBook, &numberOfContacts);
	if (!errorOpenFile)
	{
		while (1)
		{
			// Выводим пользователю команды и даем выбор
			printCommands();
			int choice;
			scanf_s("%d", &choice);
			printf("\n");

			switch (choice)
			{
			case 0:
				return 0;
			case 1:
				addContact(phoneBook, &numberOfContacts);
				break;
			case 2:
				printf("%d\n", numberOfContacts);
				printContacts(phoneBook, numberOfContacts);
				break;
			case 3:
				findPhoneNumber(phoneBook, numberOfContacts);
				break;
			case 4:
				findName(phoneBook, numberOfContacts);
				break;
			case 5:
				saveData(phoneBook, numberOfContacts);
				printf("Данные успешно сохранены!\n");
				printf("\n");
				break;
			default:
				printf("Некорректный ввод данных, попробуйте еще раз");
				break;
			}
		}
		return 0;
	}
	return errorOpenFile;
}