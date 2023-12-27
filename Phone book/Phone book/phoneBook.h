#pragma once

#include <stdlib.h>
#include <limits.h>

#define MAX_NAME_LENGTH 50
#define MAX_PHONE_NUMBER_LENGTH 20
#define MAX_CONTACTS_NUMBER 100
#define BREAK_POINT INT_MAX

typedef enum
{
    success,
    outOfMemory = 2,
    openFileError,
    copyError
} ErrorCode;

typedef enum
{
    exitCommand,
    addContactCommand,
    printContactsCommand,
    findPhoneNumberByNameCommand,
    findNameByPhoneNumberCommand,
    saveContactsCommand
} Command;

typedef struct PhoneBook
{
    char name[MAX_NAME_LENGTH];
    char phoneNumber[MAX_PHONE_NUMBER_LENGTH];
} PhoneBook;

// Get data from a file
ErrorCode initData(PhoneBook phoneBook[MAX_CONTACTS_NUMBER], const char* const fileNameToOpen, size_t* const numberOfContacts);

// Add contact in phone book
ErrorCode addContact(PhoneBook phoneBook[MAX_CONTACTS_NUMBER], const char name[MAX_NAME_LENGTH], const char phoneNumber[MAX_PHONE_NUMBER_LENGTH],
    size_t* const numberOfContacts);

// Print all contacts in phone book
void printContacts(const PhoneBook phoneBook[MAX_CONTACTS_NUMBER], const size_t numberOfContacts);

// Find all contacts that match part of contact, entered by user
// Return suitable indexes in phone book
size_t* findContactsByPartOfContact(const PhoneBook phoneBook[MAX_CONTACTS_NUMBER], const char* const partOfContact, const int choice, const size_t numberOfContacts);

// Print contacts that match part of contact, entered by user
void printSuitableContacts(const PhoneBook phoneBook[MAX_CONTACTS_NUMBER], const size_t* const suitableContacts, const int choice);

// Save phone book to file
ErrorCode saveData(const PhoneBook phoneBook[MAX_CONTACTS_NUMBER], const char* const fileNameToWrite, const size_t numberOfContacts);

// Print commands for user
void printCommands(void);
